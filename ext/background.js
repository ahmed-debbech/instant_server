chrome.runtime.onInstalled.addListener(() => {
  console.log('the extension is installed successfully');
});

setInterval(() => {
  console.log('calling...');
  fetch('http://localhost:9880/')
  .then((res) => {res.text().then((data) => {
    console.log("successful!")
    
    chrome.tabs.query({ active: true, currentWindow: true }, function (tabs) {
      console.log(tabs)
      if(tabs.length > 0){
        chrome.tabs.sendMessage(tabs[0].id, { message: "myMessage" }, (res) => {
          console.log("tab response: ", res)
        });
      }
    });
  })})
  .catch((err) => {console.log("could not connect to host")})
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