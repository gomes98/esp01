<template>
  <div>
    <div class="modal" id="myModal" style="display: block; overflow: auto">
      <div class="modal-dialog">
        <div class="modal-content">
          <!-- Modal Header -->
          <div class="modal-header d-inline-flex">
            <h4 class="modal-title">Chat</h4>
            <button
              type="button"
              class="close"
              @click="$emit('close')"
              data-dismiss="modal"
            >
              ×
            </button>
          </div>
          <!-- Modal body -->
          <div class="modal-body">
            <div class="form-row">
              <div class="form-group col">
                <input type="text" class="form-control" id="chatName" placeholder="Seu NickName" v-model="nickName" />
              </div>
            </div>
            <div class="form-row">
              <div class="form-group col">
                <label for="rcvMsg">Mensagens</label>
                <textarea class="form-control" id="rcvMsg" rows="10" v-model="value" readonly></textarea>
              </div>
            </div>
            <div class="form-row">
              <div class="form-group col-10">
               <input type="text" class="form-control" id="toSend" placeholder="Texto para Enviar" v-model="mensagem" :disabled="nickName.length ==0" />
              </div>
              <div class="form-group col-2">
               <button class="btn btn-success form-control" @click="send" :disabled="nickName.length ==0">Enviar</button>
              </div>
            </div>
          </div>
        </div>
      </div>
    </div>
  </div>
</template>

<script>
export default {
  name: "modalWifi",
  props: ['value'],
  data: () => ({
    // mensagens: [],
    mensagem:'',
    nickName: ''
  }),
  methods: {
    send() {
      localStorage.setItem('nick', this.nickName)
      let formData = new FormData();
      let chat = {chat: true, nickName: this.nickName, mensagem: this.mensagem}
      formData.append("data", JSON.stringify(chat));
      this.$http
        .post(`/sse`, formData, {
          headers: {
            "Content-Type": "multipart/form-data",
          },
        })
        .then(() => {
        });
    },
  },
    mounted() {
      let nick = localStorage.getItem('nick') 
      if(nick){
        this.nickName = nick
      }
    },
};
</script>

<style>
</style>