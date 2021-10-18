<template>
  <div>
    <div class="modal" id="myModal" style="display: block; overflow: auto">
      <div class="modal-dialog">
        <div class="modal-content">
          <!-- Modal Header -->
          <div class="modal-header d-inline-flex">
            <h4 class="modal-title">Enviar Arquivo</h4>
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
                <label for="exampleFormControlFile1">Seu Nick</label>
                <input
                  type="text"
                  class="form-control"
                  id="chatName"
                  placeholder="Seu NickName"
                  v-model="nickName"
                  disabled
                />
              </div>
            </div>
            <div class="form-group">
              <input
                type="file"
                class="form-control-file"
                id="file"
                @change="sliptFile"
              />
            </div>
            <div class="form-row  right-0">
              <div class="form-group col-2">
                <button
                  class="btn btn-success form-control"
                  @click="send"
                  :disabled="nickName.length == 0"
                >
                  Enviar
                </button>
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
  props: ["value"],
  data: () => ({
    // mensagens: [],
    mensagem: "",
    nickName: "",
    fileParts: [],
  }),
  methods: {
    send() {
      localStorage.setItem("nick", this.nickName);
      let formData = new FormData();
      let chat = {
        chat: true,
        nickName: this.nickName,
        mensagem: this.mensagem,
      };
      formData.append("data", JSON.stringify(chat));
      this.$http
        .post(`/sse`, formData, {
          headers: {
            "Content-Type": "multipart/form-data",
          },
        })
        .then(() => {});
    },
    sliptFile(e){
      console.log(e.srcElement.files[0]);
      let reader = new FileReader()
      reader.onload = () =>{
        let d = reader.result
        // console.log(d);
        // console.log(d.length)
        let partes = d.length / 500
        // console.log(partes)
        let parte = []
        let loop = 0
        do {
          console.log(loop, partes);
          parte.push(d.substring((500*loop),(loop*500)+500))
          loop ++;
        } while (loop < partes );
          // parte.push(d.substring((500*loop)))
        console.log(parte);
        // console.log(JSON.stringify(parte).length);
        // console.log(reader.result);
        }
      reader.readAsDataURL(e.srcElement.files[0])
    }
  },
  mounted() {
    let nick = localStorage.getItem("nick");
    if (nick) {
      this.nickName = nick;
    }
  },
};
</script>

<style>
</style>