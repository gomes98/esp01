<template>
  <div>
    <div class="modal" id="myModal" style="display: block; overflow: auto" >
      <div class="modal-dialog">
        <div class="modal-content">
          <!-- Modal Header -->
          <div class="modal-header d-inline-flex">
            <h4 class="modal-title">Redes Disponiveis</h4>
            <button class="btn ml-auto p-2" type="button" @click="loadWifi"><img src="../../src/assets/refresh.png" width="20"></button>
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
            <table class="table" v-if="!ssid">
              <thead>
                <tr>
                  <th scope="col">SSID</th>
                  <th scope="col">Sinal</th>
                  <th scope="col">Segura</th>
                  <th scope="col">Ingresar</th>
                </tr>
              </thead>
              <tbody>
                <tr v-for="(item, i) in wifi" :key="i">
                  <td>{{ item.ssid }}</td>
                  <td>{{ item.rssi }}</td>
                  <td>{{ item.secure > 0 ? "SIM" : "NÃO" }}</td>
                  <td>
                    <button
                      @click="ssid = item.ssid"
                      class="btn bg-success text-white"
                    >
                      Conectar
                    </button>
                  </td>
                </tr>
              </tbody>
            </table>
            <form>
              <div class="form-group" v-if="ssid">
                <label for="exampleFormControlInput1">Nome da Rede</label>
                <input
                  type="text"
                  class="form-control"
                  id="exampleFormControlInput1"
                  v-model="ssid"
                />
                <label for="exam1">Senha da Rede</label>
                <input
                  type="text"
                  class="form-control"
                  id="exam1"
                  v-model="password"
                />
                <div class="d-flex flex-row justify-content-around mt-2">
                  <button class="btn btn-lg btn-warning" @click="ssid =''">
                    Limpar
                  </button>
                  <button class="btn btn-lg btn-success" @click.prevent="conWifi" >
                    Conectar
                  </button>
                </div>
              </div>
            </form>
          </div>
          <!-- Modal footer -->
          <div class="modal-footer">
            <button
              type="button"
              @click="$emit('close')"
              class="btn btn-danger"
              data-dismiss="modal"
            >
              Fechar
            </button>
          </div>
        </div>
      </div>
    </div>
  </div>
</template>

<script>
export default {
  name: "modalWifi",
  data: () => ({
    wifi: [],
    ssid: "",
    password: "",
  }),
  methods: {
    loadWifi() {
      this.$http(`/scan`).then((resp) => {
        this.wifi = resp.data;
      });
    },
    conWifi() {
      let formData = new FormData();
      formData.append("ssid", this.ssid);
      formData.append("password", this.password);
      this.$http
        .post(`/wifi`, formData, {
          headers: {
            "Content-Type": "multipart/form-data",
          },
        })
        .then(() => {
            this.$emit('close')
        });
    },
  },
};
</script>

<style>
</style>