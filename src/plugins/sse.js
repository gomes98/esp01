let sseClient 

const start = async ()=>{
    sseClient = new EventSource("http://192.168.88.31/events");
    sseClient.onopen = function (evt) {console.log(evt);};
    sseClient.onerror = function (evt) {console.log(evt);};
}

const callback = function (event, callback){
    sseClient.addEventListener(event, callback, false);
}

module.exports = {
    start,
    callback
}