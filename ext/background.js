chrome.runtime.onInstalled.addListener(() => {
  console.log('the extension is installed successfully');
});
setInterval(() => {
  console.log('calling...');
  chrome.storage.local.get(["pip"], (d) =>{
    console.log(d)
    fetch("http://192.168.1."+r+":9880")
    .then((res) => {res.text().then((data) => {
      console.log("successful!")
      
      chrome.tabs.query({ active: true, currentWindow: true }, function (tabs) {
        console.log(tabs)
        if(tabs.length > 0){
          if(data != "nothing"){
            chrome.action.setIcon({
              path: {
                16: "notif.png",
                32: "notif.png"
              },
            });
          }
        }
      });
    })})
    .catch((err) => {console.log("could not connect to host")})
  })
}, 1000);


/*chrome.tabs.onActivated.addListener(function(info){
  chrome.tabs.get(info.tabId, function(change){
    setInterval(() => {
      console.log('calling...');
      fetch('http://localhost:9880/')
      .then((res) => {res.text().then((data) => {
        console.log("successful!")
        
        if(matching) {
          chrome.browserAction.setIcon({path: 'images.png', tabId: info.tabId});
          return;
        } else {
            chrome.browserAction.setIcon({path: 'images.png', tabId: info.tabId});
        }
      })})
      .catch((err) => {console.log("could not connect to host")})
    }, 1000);
  });
});*/