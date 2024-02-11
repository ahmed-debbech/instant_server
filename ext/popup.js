function send(){
    let v = document.getElementById("paste").value;
    alert(v)
    fetch('http://57.129.15.180:3000/copy', {
        method: 'POST',
        body: JSON.stringify({
            text: v
        }),
        headers : {
            "Content-Type" : "application/json"
        }
      })
}
function onTestChange() {
    var key = window.event.keyCode;

    // If the user has pressed enter
    if (key == 13) {
        send()
    }
   
}
document.getElementById("aa").addEventListener('click', () => {
    send()
})
document.getElementById("paste").addEventListener('onkeypress', () => {
    onTestChange()
})