chrome.runtime.onInstalled.addListener(() => {
  console.log('the extension is installed successfully');
});
setInterval(() => {
  console.log('calling...');
  chrome.storage.local.get(["pip"], (d) =>{
    console.log(JSON.stringify(d))
    fetch("http://192.168.1."+d.pip+":9880")
    .then((res) => {res.text().then((data) => {
      console.log("successful!")
      
      chrome.tabs.query({ active: true, currentWindow: true }, function (tabs) {
        console.log(tabs)
        if(tabs.length > 0){
          if(data != "nothing"){
            chrome.storage.local.get(["seend"], (dsn) =>{
              console.log(dsn)
              if(dsn.seend != data){
                chrome.action.setIcon({
                  path: {
                    16: "notif.png",
                    32: "notif.png"
                  },
                });
              }
              chrome.storage.local.set({"seend": data}, (d) =>{})
            });
          }
        }
      });
    })})
    .catch((err) => {console.log("could not connect to host")})
  })
}, 1000);

