function send(){
    let v = document.getElementById("in-msg").value;
    if(v == "") return;
    alert(v)
    chrome.storage.local.get(["pip"], async (d) =>{
        await fetch("http://192.168.1."+d.pip+":9880", {
            method: "POST",
            body: v,
        });
        document.getElementById("msg").value = v;
    })
}

function storeIp(){
    let v = document.getElementById("ip-val").value;
    //localStorage.setItem("pip", v)
    chrome.storage.local.set({"pip": v}, (d) =>{})
}

document.getElementById("aa").addEventListener('click', () => {
    storeIp()
    send()
})

let ipps
function refresh(){ 
    storeIp()

    chrome.storage.local.get(["pip"], (d) =>{

        chrome.storage.local.get((["seend"]), (da) =>{
            document.getElementById("msg").value = da.seend
            chrome.storage.local.set({"seend": da.seend}, (d) =>{})
            ipps = d.pip;
            document.getElementById("ip-val").value = ipps; 
            chrome.action.setIcon({
                path: {
                16: "images.png",
                32: "images.png"
                },
            });
        });
    })
}
document.getElementById("in-msg").addEventListener('click', () => {
    refresh()
})
