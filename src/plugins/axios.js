import Vue from 'vue'
import axios from 'axios'

// axios.defaults.baseURL = 'http://192.168.88.33'

const success = res => res
const error = res => res


axios.interceptors.response.use(success, error)

Vue.use({
    install(Vue) {
        Vue.prototype.$http = axios
    }
})