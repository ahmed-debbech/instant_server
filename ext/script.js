/**
 * 
 */

chrome.runtime.onMessage.addListener((message, sender, sendResponse) => {
    console.log(message)
});
chrome.action.onClicked.addListener(
    () => {
     console.log("eoeoeo")
    }
  )