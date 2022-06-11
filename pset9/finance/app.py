import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session, jsonify
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash
import datetime

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    portfolio = db.execute("SELECT * FROM portfolio where user_id = ?", session["user_id"])
    cash = float("{:.2f}".format(db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]))
    total = cash
    for row in portfolio:
        row["name"] = lookup(row["symbol"])["name"]
        row["price"] = float(lookup(row["symbol"])["price"])
        row["total"] = float("{:.2f}".format(row["price"] * row["shares"]))
        total += float(row["total"])
        row["price"] = usd(row["price"])
        row["total"] = usd(row["total"])
    cash = usd(cash)
    total = usd(total)
    return render_template("index.html", portfolio=portfolio, cash=cash, total=total)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 400)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    # Forget any user_id
    session.clear()

    if request.method == "POST":

        # Ensure username is not empty
        not_accepted = ["", " "]
        if request.form.get("username") in not_accepted:
            return apology("username not accepted", 400)

        # Check if duplicate username
        usernames = db.execute("SELECT username FROM users")
        for i in range(len(usernames)):
            usernames[i] = usernames[i]['username']
        if request.form.get("username") in usernames:
            return apology("username exists, please pick another", 400)

        # Ensure password is not empty
        elif request.form.get("password") in not_accepted:
            return apology("password not accepted", 400)

        # Ensure password confirmation is same as password
        elif request.form.get("confirmation") != request.form.get("password"):
            return apology("password does not match", 400)

        else:
            db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", request.form.get("username"), generate_password_hash(request.form.get("password")))
            return redirect("/login")

    else:
        return render_template("register.html")


@app.route("/quote", methods=["GET", "POST"])
def quote():
    if request.method == "POST":
        stock = lookup(request.form.get("symbol"))
        if stock:
            stock["price"] = usd(stock["price"])
            return render_template("quote.html", stock=stock)
        else:
            return apology("symbol does not exist", 400)
    else:
        return render_template("quote.html")


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":

        # Check if form input is empty
        not_allowed = ["", " ", None, 0, '0']
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")
        if symbol in not_allowed or shares in not_allowed:
            return apology("please input symbol and shares", 400)

        # Check if shares is a number
        try:
            int(shares)
        except:
            return apology("please input number as shares", 400)

        # Check if shares is a float
        if float(shares) - int(shares):
            return apology("please input a round number", 400)

        # Check if shares is a float
        if int(shares) < 0:
            return apology("please input a positive number", 400)

        shares = int(shares)

        # Check if symbol doesn't exist
        if lookup(symbol) in not_allowed:
            return apology("symbol does not exist", 400)

        price = lookup(symbol)["price"]
        total = price * shares

        # Check if there's enough cash
        bal = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"] - total
        if bal < 0:
            return apology("not enough cash", 400)

        # History
        timestamp = datetime.datetime.now().strftime("%Y/%m/%d %H:%M:%S")
        db.execute("INSERT INTO history (user_id,symbol,price,shares,timestamp,type) VALUES (?,?,?,?,?,'buy')", session["user_id"], symbol, price, shares, timestamp)

        # Users
        db.execute("UPDATE users SET cash = ? WHERE id = ?", bal, session["user_id"])

        # Portfolio
        if len(db.execute("SELECT shares FROM portfolio WHERE user_id = ? AND symbol = ?", session["user_id"], symbol)):
            shares = int(db.execute("SELECT shares FROM portfolio WHERE user_id = ? AND symbol = ?", session["user_id"], symbol)[0]["shares"]) + shares
            db.execute("UPDATE portfolio SET shares = ? WHERE user_id = ? AND symbol = ?", shares, session["user_id"], symbol)
        else:
            db.execute("INSERT INTO portfolio (user_id, symbol, shares) VALUES (?,?,?)", session["user_id"], symbol, shares)

        flash("Bought!")
        return redirect("/")

    else:
        return render_template("buy.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":

        # Check if form input is empty
        not_allowed = ["", " ", None, 0, '0']
        symbol = request.form.get("symbol")
        sold = request.form.get("shares")
        if symbol in not_allowed or sold in not_allowed:
            return apology("please input symbol and shares", 400)

        # Check if shares is a number
        try:
            int(sold)
        except:
            return apology("please input number as shares", 400)

        # Check if shares is a float
        if float(sold) - int(sold):
            return apology("please input a round number", 400)

        # Check if shares is a float
        if int(sold) < 0:
            return apology("please input a positive number", 400)

        sold = int(sold)

        # Check if user has stock for that symbol
        shares = db.execute("SELECT shares FROM portfolio WHERE user_id = ? AND symbol = ?", session["user_id"], symbol)
        if not shares:
            return apology(f"you have no shares in {symbol}", 400)

        shares = int(shares[0]["shares"])

        # Check if user has enough shares
        if sold > shares:
            return apology("you don't have that many shares", 400)

        # Users
        price = lookup(symbol)["price"]
        cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"] + price * sold
        db.execute("UPDATE users SET cash = ? WHERE id = ?", cash, session["user_id"])

        # Portfolio
        if shares-sold == 0:
            db.execute("DELETE FROM portfolio WHERE user_id = ? AND symbol = ?", session["user_id"], symbol)
        else:
            db.execute("UPDATE portfolio SET shares = ? WHERE user_id = ? AND symbol = ?", shares-sold, session["user_id"], symbol)

        # History
        timestamp = datetime.datetime.now().strftime("%Y/%m/%d %H:%M:%S")
        db.execute("INSERT INTO history (user_id, symbol, price, shares, timestamp, type) VALUES (?,?,?,?,?,'sell')", session["user_id"], symbol, price, 0-sold, timestamp)

        flash("Sold!")
        return redirect("/")

    else:
        portfolio = db.execute("SELECT symbol, shares FROM portfolio WHERE user_id = ?", session["user_id"])
        return render_template("sell.html", portfolio=portfolio)


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    history = db.execute("SELECT * FROM history WHERE user_id = ?", session["user_id"])
    return render_template("history.html", history=history)


@app.route("/reset", methods=["GET", "POST"])
@login_required
def reset():
    db.execute("UPDATE users SET cash = 10000 where id = ?", session["user_id"])
    db.execute("DELETE FROM history WHERE user_id = ?", session["user_id"])
    db.execute("DELETE FROM portfolio WHERE user_id = ?", session["user_id"])
    flash("Reset successful")
    return redirect("/")

