import Vue from 'vue'
import App from './App.vue'
import './plugins/axios'

Vue.config.productionTip = false

new Vue({
  // store,
  // vuetify,
  render: h => h(App)
}).$mount('#app')
