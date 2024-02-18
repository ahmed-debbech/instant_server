function send(){
    let v = document.getElementById("in-msg").value;
    let b = document.getElementById("ip-val").value;

    if(v == "" || b == "") return;
    chrome.storage.local.get(["pip", "port"], async (d) =>{
        await fetch("http://192.168.1."+d.pip+":"+d.port, {
            method: "POST",
            body: v,
        });
        document.getElementById("msg").innerText = v;
        document.getElementById("in-msg").value=""
        chrome.storage.local.set({"seend": v}, (d) =>{})
    })
}

function storeIp(){
    let v = document.getElementById("ip-val").value;
    //localStorage.setItem("pip", v)
    chrome.storage.local.set({"pip": v}, (d) =>{})
}

document.getElementById("aa").addEventListener('click', () => {
    if(document.getElementById('ip-val').value == "" || document.getElementById('in-msg').value == "") return;
    storeIp()
    send()
})

document.getElementById("ip-val").addEventListener('onblur', () => {
    console.log("eeee")
    if(document.getElementById('ip-val').value == "") return;
    storeIp()
})

let ipps
function refresh(){ 

    chrome.storage.local.get(["pip"], (d) =>{

        chrome.storage.local.get((["seend"]), (da) =>{
            if(da.seend)
                document.getElementById("msg").innerText = da.seend
            
            chrome.storage.local.set({"seend": da.seend}, (d) =>{})
            ipps = d.pip;
            if(document.getElementById("ip-val").value != ""){
                chrome.storage.local.set({"pip": document.getElementById("ip-val").value}, (d) =>{})
            }else{
                if(ipps)
                    document.getElementById("ip-val").value = ipps; 
            }
            chrome.action.setIcon({
                path: {
                16: "images.png",
                32: "images.png"
                },
            });
        });
    })
}

function unlock(){
    document.getElementById("boddy").hidden = false;
    document.getElementById("back").hidden = true;
}

document.getElementById("in-msg").addEventListener('click', () => {
    refresh()
})
document.getElementById("back").addEventListener('click', () => {
    unlock()
})
