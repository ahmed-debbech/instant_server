chrome.runtime.onInstalled.addListener(() => {
  console.log('the extension is installed successfully');
  chrome.storage.local.set({"port": "9880"}, (d) =>{})
});

setInterval(() => {
  console.log('calling...');
  chrome.storage.local.get(["pip", "port"], (d) =>{
    console.log(JSON.stringify(d))
    if(!d.pip || !d.port) return;
    fetch("http://192.168.1."+d.pip+":" + d.port)
    .then((res) => {res.text().then((data) => {
      console.log("successful!")
      
      chrome.tabs.query({ active: true, currentWindow: true }, function (tabs) {
        if(tabs.length > 0){
          if(data != "nothing"){
            chrome.storage.local.get(["seend"], (dsn) =>{
              console.log(dsn.seend)
              if(!data.includes(dsn.seend)){
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
    .catch((err) => {
      let newport = Number(d.port);
      newport++;
      if(newport > 9890) newport = "9880"
      console.log("could not connect to host.. changing port to" + newport)
      chrome.storage.local.set({"port": newport}, (d) =>{})

    })
  })
}, 1000);

