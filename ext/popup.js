async function send(){
    let v = document.getElementById("in-msg").value;
    alert(v)
    await fetch("http://192.168.1."+getIp()+":9880", {
        method: "POST",
        body: JSON.stringify(v),
    });
}
function onTestChange() {
    var key = window.event.keyCode;

    // If the user has pressed enter
    if (key == 13) {
        send()
    }
   
}
function storeIp(){
    let v = document.getElementById("ip-val").value;
    localStorage.setItem("pip", v)
}
function getIp(){
    let x = localStorage.getItem("pip")
    if(x){
        document.getElementById("ip-val").value = x;
        return x
    }
    return null;
}
document.getElementById("aa").addEventListener('click', () => {
    send()
    storeIp()
})
function refresh(){ 
    getIp()
    chrome.action.setIcon({
        path: {
          16: "images.png",
          32: "images.png"
        },
      });
}
document.getElementById("in-msg").addEventListener('click', () => {
    refresh()
})
