import Vue from 'vue'
import axios from 'axios'

if (process.env.NODE_ENV === 'production') {
    axios.defaults.baseURL = '/'
} else {
    axios.defaults.baseURL = 'http://192.168.88.27/'
}

const success = res => res
const error = res => res


axios.interceptors.response.use(success, error)

Vue.use({
    install(Vue) {
        Vue.prototype.$http = axios
    }
})