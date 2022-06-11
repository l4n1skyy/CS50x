
CREATE TABLE users (id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, username TEXT NOT NULL, hash TEXT NOT NULL, cash NUMERIC NOT NULL DEFAULT 10000.00);
CREATE TABLE sqlite_sequence(name,seq);
CREATE UNIQUE INDEX username ON users (username);

CREATE TABLE history (
    id INTEGER NOT NULL,
    user_id INTEGER NOT NULL,
    symbol TEXT NOT NULL,
    price NUMERIC NOT NULL,
    shares INTEGER NOT NULL,
    timestamp DATETIME NOT NULL,
    type TEXT NOT NULL,
    PRIMARY KEY(id),
    FOREIGN KEY(user_id) REFERENCES users(id)
);

CREATE TABLE portfolio (
    id INTEGER NOT NULL,
    user_id INTEGER NOT NULL,
    symbol TEXT NOT NULL,
    shares INTEGER NOT NULL,
    PRIMARY KEY(id),
    FOREIGN KEY(user_id) REFERENCES users(id)
);

INSERT INTO history (user_id,symbol,price,shares,timestamp,type) VALUES (1,'NFLX',202.83,2,'2022/06/09 02:14:25','buy');