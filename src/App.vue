<template>
  <div class="m-1">
    <div class="accordion" id="accordionExample">
      <div class="card">
        <div class="card-header" id="headingOne">
          <h2 class="mb-0">
            <div class="d-flex bd-highlight mb-0">
              <div class="p-2 flex-grow-1 bd-highlight">
                <button
                  @click="collapseNetwork = !collapseNetwork"
                  class="btn btn-link btn-block text-left"
                  type="button"
                  data-toggle="collapse"
                  data-target="#collapseOne"
                  aria-expanded="true"
                  aria-controls="collapseOne"
                >
                  Rede                </button>
              </div>
              <div class="p-2 bd-highlight">
                <button
                  @click="loadData()"
                  class="btn btn-outline-secondary btn-sm m-0 p-0"
                >
                  <img src="@/assets/ac.svg" width="20" />
                </button>
              </div>
            </div>
          </h2>
        </div>

        <div
          id="collapseOne"
          class="collapse"
          :class="collapseNetwork ? 'show' : 'hide'"
          aria-labelledby="headingOne"
          data-parent="#accordionExample"
        >
          <div class="card-body">
            <div class="card-body">
              <div>
                <div class="d-flex flex-row justify-content-around flex-wrap">
                  <p class="mx-1">
                    <strong>IP: </strong>
                    <small>{{ wifi.ip }}</small>
                  </p>
                  <p class="mx-1">
                    <strong>MAC: </strong>
                    <small>{{ wifi.mac }}</small>
                  </p>
                  <p class="mx-1">
                    <strong>Nome da Rede: </strong>
                    <small>{{ wifi.SSID }}</small>
                  </p>
                  <p class="mx-1">
                    <strong>Sinal: </strong>
                    <small>{{ wifi.RSSI }}</small>
                  </p>
                  <p class="mx-1">
                    <strong>Hostname: </strong>
                    <small>{{ wifi.hostname }}</small>
                  </p>
                  <p class="mx-1">
                    <strong>Status Wifi: </strong>
                    <small>{{ stsWifi[wifi.status] }}</small>
                  </p>
                  <button
                    class="btn btn-outline-secondary ml-auto p-2"
                    @click="modalApi = true"
                  >
                    <img src="../src/assets/c.svg" width="20" /> API
                  </button>
                  <button
                    class="btn btn-outline-secondary ml-auto p-2"
                    @click="modalCfg = true"
                  >
                    <img src="../src/assets/g.svg" width="20" /> Cfg
                  </button>
                  <button
                    class="btn btn-outline-secondary ml-auto p-2"
                    @click="modalWifi = true"
                  >
                    <img src="../src/assets/wf.svg" width="20" /> Selecionar
                  </button>
                </div>
              </div>
            </div>
          </div>
        </div>
      </div>
      <div class="card my-1">
        <div class="card-header" id="headingTwo">
          <h2 class="mb-0">
            <button
              class="btn btn-link btn-block text-left"
              @click="collapseOutput = !collapseOutput"
              type="button"
              data-toggle="collapse"
              data-target="#collapseTwo"
              aria-expanded="false"
              aria-controls="collapseTwo"
            >
              Saídas
            </button>
          </h2>
        </div>
        <div
          id="collapseTwo"
          class="collapse"
          :class="collapseOutput ? 'show' : ''"
          aria-labelledby="headingTwo"
          data-parent="#accordionExample"
        >
          <div class="card-body">
            <div class="d-flex flex-row justify-content-around flex-wrap">
              <Output
                v-model="g1"
                :config="config.o1"
                :out="setOutput"
                :pin="1"
              />
              <Output
                v-model="g2"
                :config="config.o2"
                :out="setOutput"
                :pin="2"
              />
            </div>
          </div>
        </div>
      </div>
      <div class="card">
        <div class="card-header" id="headingThree">
          <h2 class="mb-0">
            <button
              class="btn btn-link btn-block text-left collapsed"
              @click="collapseImput = !collapseImput"
              type="button"
              data-toggle="collapse"
              data-target="#collapseThree"
              aria-expanded="false"
              aria-controls="collapseThree"
            >
              Entradas
            </button>
          </h2>
        </div>
        <div
          id="collapseThree"
          class="collapse"
          :class="collapseImput ? 'show' : ''"
          aria-labelledby="headingThree"
          data-parent="#accordionExample"
        >
          <div class="card-body">
            <div class="d-flex flex-row justify-content-around flex-wrap">
              <Input v-model="i1" :config="config.i1" :pin="1" />
              <Input v-model="i2" :config="config.i2" :pin="2" />
            </div>
          </div>
        </div>
      </div>
    </div>
    <Modal v-if="modalWifi" @close="modalWifi = false" />
    <ModalAPI v-if="modalApi" @close="modalApi = false" />
    <ModalCFG
      v-if="modalCfg"
      @close="modalCfg = false"
      v-model="config"
      @save="saveCFG"
    />
    <div
      class="position-fixed bottom-0 right-0 p-3"
      style="z-index: 5; right: 0; bottom: 0"
    >
      <div v-for="(item, index) in toasts" :key="index">
        <Toast :data="item" :number="index" @remove="removeToast($event)" />
      </div>
    </div>
    <div
      class="position-fixed bottom-0 left-0 p-3"
      style="z-index: 5; left: 0; bottom: 0"
    >
      <button
        type="button"
        class="btn btn-warning rounded-circle p-1"
        @click="modalChat = true"
      >
        <img src="../src/assets/ct.svg" class="m-1" width="20" />
      </button>
      <br />
      <br />
      <button
        type="button"
        class="btn btn-primary rounded-circle p-1"
        @click="modalFile = true"
      >
        <img src="../src/assets/ct.svg" class="m-1" width="20" />
      </button>
    </div>
    <Chat v-if="modalChat" @close="modalChat = false" v-model="mensagens" />
    <File v-if="modalFile" @close="modalFile = false" />
  </div>
</template>

<script>
import sse from './plugins/sse'
import config from './data/config.json'
export default {
  name: "App",
  components: {
    Modal: () => import("./components/modal.vue"),
    ModalAPI: () => import("./components/modalAPI.vue"),
    ModalCFG: () => import("./components/modalCfg.vue"),
    Toast: () => import("./components/toast.vue"),
    Output: () => import("./components/output.vue"),
    Input: () => import("./components/input.vue"),
    Chat: () => import("./components/mdChat.vue"),
    File: () => import("./components/mdFile.vue"),
  },
  data: () => ({
    // sseClient: {},
    modalWifi: false,
    modalApi: false,
    modalCfg: false,
    modalChat: false,
    modalFile: false,
    modalSound1: false,
    modalSound2: false,
    hideInToast: true,
    sound: null,
    collapseNetwork: false,
    collapseOutput: true,
    collapseImput: true,
    mensagens: "",
    g1: 0,
    g2: 0,
    i1: 0,
    i2: 0,
    toasts: [],
    wifi: {},
    stsWifi: [
      "Idle",
      "Rede não encontrada",
      "Scan Completo",
      "Conectado",
      "Conexão Falhou (Senha)",
      "Conexão Perdida",
      "Desconectado",
    ],
    config
  }),
  methods: {
    setOutput(out, value, timeout) {
      let formData = new FormData();
      formData.append(`gpio${out}`, value);
      if (timeout) {
        formData.append(`timeout`, timeout);
      }
      if (
        out == 1 &&
        this.config.o1.timeout > 0 &&
        this.config.o1.timeoutEnabled
      ) {
        formData.append(`timeout`, this.config.o1.timeout);
      }
      if (
        out == 2 &&
        this.config.o2.timeout > 0 &&
        this.config.o2.timeoutEnabled
      ) {
        formData.append(`timeout`, this.config.o2.timeout);
      }
      this.$http
        .post(`/gpio`, formData, {
          headers: {
            "Content-Type": "multipart/form-data",
          },
        })
        .then(() => {});
    },
    loadGpio() {
      this.$http(`/gpio`).then((resp) => {
        this.g1 = resp.data.gpio1;
        this.g2 = resp.data.gpio2;
      });
    },
    loadInput() {
      this.$http(`/input`).then((resp) => {
        this.i1 = resp.data.in1;
        this.i2 = resp.data.in2;
      });
    },
    loadWifi() {
      this.$http(`/wstat`).then((resp) => {
        this.wifi = resp.data;
      });
    },
    playSound(url) {
      if (this.sound) {
        this.sound.pause();
      }
      if (url) {
        this.sound = new Audio(url);
        this.sound.play();
      }
    },
    output(value) {
      let data = JSON.parse(value.data);
      if (data.gpio1 != null) {
        this.g1 = data.gpio1;
        this.addToast({
          hideInToast: false,
          title: "Saída",
          body: `Saída 1 ${data.gpio1 ? "Ligada" : "Desligada"}`,
          add: new Date().getTime(),
          classTitle: `${
            data.gpio1
              ? this.config.o1.cardOnClass
              : this.config.o1.cardOffClass
          }`,
        });
        if (this.config.o1.enableSound) {
          this.playSound(
            data.in1 ? this.config.o1.onSound : this.config.o1.offSound
          );
        }
      }
      if (data.gpio2 != null) {
        this.addToast({
          hideInToast: false,
          title: "Saída",
          body: `Saída 2 ${data.gpio2 ? "Ligada" : "Desligada"}`,
          add: new Date().getTime(),
          classTitle: `${
            data.gpio2
              ? this.config.o1.cardOnClass
              : this.config.o2.cardOffClass
          }`,
        });
        this.g2 = data.gpio2;
        if (this.config.o2.enableSound) {
          this.playSound(
            data.in1 ? this.config.o2.onSound : this.config.o2.offSound
          );
        }
      }
    },
    addToast(data) {
      this.toasts.push(data);
    },
    input(value) {
      let data = JSON.parse(value.data);
      if (data.in1 != null) {
        this.i1 = data.in1;
        this.addToast({
          hideInToast: false, 
          title: "Entrada",
          body: `Entrada 1 ${data.in1 ? "Desligada" : "Ligada"}`,
          add: new Date().getTime(),
          classTitle: `${
            data.in1 ? this.config.i1.offClass : this.config.i1.onClass
          }`,
        });
        if (this.config.i1.enableSound) {
          this.playSound(
            data.in1 ? this.config.i1.offSound : this.config.i1.onSound
          );
        }
      }
      if (data.in2 != null) {
        this.i2 = data.in2;
        this.addToast({
          hideInToast: false,
          title: "Entrada",
          body: `Entrada 2 ${data.in2 ? "Desligada" : "Ligada"}`,
          add: new Date().getTime(),
          classTitle: `${
            data.in2 ? this.config.i2.offClass : this.config.i2.onClass
          }`,
        });
        if (this.config.i2.enableSound) {
          this.playSound(
            data.in1 ? this.config.i2.offSound : this.config.i2.onSound
          );
        }
      }
    },
    wifiATT() {
      this.loadWifi();
    },
    loadCfg() {
      this.$http(`/config`).then((resp) => {
        if (resp.status == 200) {
          this.config = resp.data;
        }
      });
    },
    saveCFG() {
      let formData = new FormData();
      formData.append(`save`, JSON.stringify(this.config));
      this.$http
        .post(`/config`, formData, {
          headers: {
            "Content-Type": "multipart/form-data",
          },
        })
        .then(() => {});
    },
    loadData() {
      this.loadGpio();
      this.loadInput();
      this.loadWifi();
      this.loadCfg();
    },
    receiveMsg(value) {
      let rcvData = JSON.parse(value.data);
      if(value.data){
        console.log(value);
      }
      if (rcvData.chat) {
        this.mensagens += `${rcvData.nickName} > ${rcvData.mensagem}\n`;
        this.addToast({
          hideInToast: false,
          title: "Chat",
          body: `Mensagem de ${rcvData.nickName}`,
          add: new Date().getTime(),
          classTitle: `bg-warning`,
        });
      }
    },
  },
  mounted() {
    sse.start();
    sse.callback("output", this.output)
    sse.callback("input", this.input)
    sse.callback("wifi", this.wifiATT)
    sse.callback("sse", this.receiveMsg)
    this.loadData();
    document.title = "ESP01 IO";

    setInterval(() => {
      let now = new Date().getTime();
      this.toasts.forEach((element, index) => {
        if (element.add + this.config.toastTime < now) {
          this.toasts.splice(index, 1);
        }
      });
    }, 500);
  },
};
</script>
<style scoped>
</style>