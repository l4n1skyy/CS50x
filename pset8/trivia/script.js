let corrects = document.querySelectorAll('.right');
let incorrects = document.querySelectorAll('.wrong')

for(let i=0; i<incorrects.length;i++){
    incorrects[i].addEventListener('click', function() {
        incorrects[i].style.backgroundColor='red';
        document.querySelector('#feedback1').innerHTML='Incorrect';
    });
}

for (let i=0; i<corrects.length;i++){
    corrects[i].addEventListener('click', function() {
        corrects[i].style.backgroundColor='green';
        document.querySelector('#feedback1').innerHTML='Correct';
    });
}

document.querySelector('form').addEventListener('submit', function(e) {
    console.log(document.querySelector('#n4').value);
    if (document.querySelector('#n4').value == '8') {
        document.querySelector('#n4').style.backgroundColor='green';
        document.querySelector('#feedback2').innerHTML='Correct';
    }
    else {
        document.querySelector('#n4').style.backgroundColor='red';
        document.querySelector('#feedback2').innerHTML='Incorrect';
    }
    e.preventDefault();
});
