const box = document.getElementById("box");
const button = document.getElementById("button");
const spinner = document.getElementById("spinner");

let timeout;
let audio = new Audio("PEDRO.mp3");;

function showPedro(){
    box.style.display = "none";
    spinner.style.visibility = "visible";
}

window.onload = function(){
    spinner.style.visibility = "hidden";

    button.addEventListener("click", () => {
        timeout = setInterval(showPedro, 26.5*1000);
        audio.play();
    });
};