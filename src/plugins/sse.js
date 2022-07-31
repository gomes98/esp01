let sseClient 

let sseUrl = '/events';

if (process.env.NODE_ENV === 'production') {
    sseUrl = '/events'
} else {
    sseUrl = 'http://192.168.88.27/events'
}

const start = async ()=>{
    sseClient = new EventSource(sseUrl);
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