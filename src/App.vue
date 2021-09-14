<template>
  <div>
    <div class="card m-1">
      <div class="card-header">
        <div class="d-flex flex-row justify-content-between flex-wrap">
          Rede
          <button
            @click="loadData()"
            class="btn btn-outline-secondary btn-sm m-0 p-0"
          >
            <img src="@/assets/arrow-clockwise.svg" width="20" />
          </button>
        </div>
      </div>
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
              API
            </button>
            <button
              class="btn btn-outline-secondary ml-auto p-2"
              @click="modalCfg = true"
            >
              Cfg
            </button>
            <button
              class="btn btn-outline-secondary ml-auto p-2"
              @click="modalWifi = true"
            >
              <img src="../src/assets/wifi.svg" width="20" /> Selecionar
            </button>
          </div>
        </div>
      </div>
    </div>
    <div class="card m-1">
      <div class="card-header d-inline-flex">Saidas</div>
      <div class="card-body">
        <div class="d-flex flex-row justify-content-around flex-wrap">
          <div class="card m-1">
            <div
              class="card-header"
              :class="g1 == 1 ? config.o1.cardOnClass : config.o1.cardOffClass"
            >
              <div class="d-flex flex-row justify-content-between flex-wrap">
                {{ config.o1.cardText }} -
                {{ g1 == 1 ? config.o1.cardOnText : config.o1.cardOffText }}
                <button
                  @click="config.o1.enableSound = !config.o1.enableSound"
                  class="btn btn-link btn-sm mx-1 p-0"
                >
                  <img
                    v-if="config.o1.enableSound"
                    src="@/assets/volume-up.svg"
                    width="20"
                  />
                  <img v-else src="@/assets/volume-mute.svg" width="20" />
                </button>
                <button @click="config.o1.timeoutEnabled = !config.o1.timeoutEnabled" class="btn btn-link btn-sm m-0 p-0">
                  <img v-if="config.o1.timeoutEnabled" src="@/assets/hourglass-split.svg" width="20" />
                  <img v-else src="@/assets/hourglass.svg" width="20" />
                </button>
              </div>
            </div>
            <div class="card-body">
              <div>
                <div class="d-flex flex-row justify-content-around flex-wrap">
                  <button
                    :class="config.o1.btnOnClass"
                    @click="setOutput(1, '1')"
                  >
                    {{ config.o1.btnOnText }}
                  </button>
                  <button
                    :class="config.o1.btnOffClass"
                    @click="setOutput(1, '0')"
                  >
                    {{ config.o1.btnOffText }}
                  </button>
                  <button
                    :class="config.o1.btnTglClass"
                    @click="setOutput(1, 't')"
                  >
                    {{ config.o1.btnTglText }}
                  </button>
                </div>
              </div>
            </div>
          </div>
          <div class="card m-1">
            <div
              class="card-header"
              :class="g2 == 1 ? config.o2.cardOnClass : config.o2.cardOffClass"
            >
              <div class="d-flex flex-row justify-content-between flex-wrap">
                {{ config.o2.cardText }} -
                {{ g2 == 1 ? config.o2.cardOnText : config.o2.cardOffText }}
                <button
                  @click="config.o2.enableSound = !config.o2.enableSound"
                  class="btn btn-link btn-sm mx-1 p-0"
                >
                  <img
                    v-if="config.o2.enableSound"
                    src="@/assets/volume-up.svg"
                    width="20"
                  />
                  <img v-else src="@/assets/volume-mute.svg" width="20" />
                </button>
                 <button @click="config.o2.timeoutEnabled = !config.o2.timeoutEnabled" class="btn btn-link btn-sm m-0 p-0">
                  <img v-if="config.o2.timeoutEnabled" src="@/assets/hourglass-split.svg" width="20" />
                  <img v-else src="@/assets/hourglass.svg" width="20" />
                </button>
              </div>
            </div>
            <div class="card-body">
              <div>
                <div class="d-flex flex-row justify-content-around flex-wrap">
                  <button
                    :class="config.o2.btnOnClass"
                    @click="setOutput(2, '1')"
                  >
                    {{ config.o2.btnOnText }}
                  </button>
                  <button
                    :class="config.o2.btnOffClass"
                    @click="setOutput(2, '0')"
                  >
                    {{ config.o2.btnOffText }}
                  </button>
                  <button
                    :class="config.o2.btnTglClass"
                    @click="setOutput(2, 't')"
                  >
                    {{ config.o2.btnTglText }}
                  </button>
                </div>
              </div>
            </div>
          </div>
        </div>
      </div>
    </div>
    <div class="card m-1">
      <div class="card-header">Entradas</div>
      <div class="card-body">
        <div class="card-body">
          <div>
            <div class="d-flex flex-row justify-content-around">
              <div class="card m-1">
                <div class="card-header">
                  <div
                    class="d-flex flex-row justify-content-between flex-wrap"
                  >
                    Entrada 1
                    <button
                      @click="config.i1.enableSound = !config.i1.enableSound"
                      class="btn btn-link btn-sm mx-1 p-0"
                    >
                      <img
                        v-if="config.i1.enableSound"
                        src="@/assets/volume-up.svg"
                        width="20"
                      />
                      <img v-else src="@/assets/volume-mute.svg" width="20" />
                    </button>
                  </div>
                </div>
                <div class="card-body">
                  <button
                    class="btn btn-lg"
                    :class="i1 == 0 ? config.i1.onClass : config.i1.offClass"
                  >
                    {{ i1 == 0 ? config.i1.onText : config.i1.offText }}
                  </button>
                </div>
              </div>
              <div class="card m-1">
                <div class="card-header">
                  <div
                    class="d-flex flex-row justify-content-between flex-wrap"
                  >
                    Entrada 2
                    <button
                      @click="config.i2.enableSound = !config.i2.enableSound"
                      class="btn btn-link btn-sm mx-1 p-0"
                    >
                      <img
                        v-if="config.i2.enableSound"
                        src="@/assets/volume-up.svg"
                        width="20"
                      />
                      <img v-else src="@/assets/volume-mute.svg" width="20" />
                    </button>
                  </div>
                </div>
                <div class="card-body">
                  <button
                    class="btn btn-lg"
                    :class="i2 == 0 ? config.i2.onClass : config.i2.offClass"
                  >
                    {{ i2 == 0 ? config.i2.onText : config.i2.offText }}
                  </button>
                </div>
              </div>
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
  </div>
</template>

<script>
import Modal from "./components/modal.vue";
import ModalAPI from "./components/modalAPI.vue";
import ModalCFG from "./components/modalCfg.vue";
import Toast from "./components/toast.vue";
import "./assets/bootstrap.min.css";
let sseClient;
export default {
  name: "App",
  components: {
    Modal,
    ModalAPI,
    ModalCFG,
    Toast,
  },
  data: () => ({
    modalWifi: false,
    modalApi: false,
    modalCfg: false,
    modalSound1: false,
    modalSound2: false,
    hideInToast: true,
    sound: null,
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
    config: {
      toastTime: 2000,
      o1: {
        enabled: true,
        cardText: "Saida 1",
        cardOnText: "Ligada",
        cardOffText: "Desligada",
        cardOnClass: "bg-success text-white",
        cardOffClass: "bg-danger text-white",
        btnOnClass: "btn btn-lg btn-success mx-4 my-1",
        btnOnText: "Liga",
        btnOffClass: "btn btn-lg btn-danger mx-4 my-1",
        btnOffText: "Desliga",
        btnTglClass: "btn btn-lg btn-warning mx-4 my-1",
        btnTglText: "Inverter",
        enableSound: true,
        onSound: "",
        offSound: "",
        timeout:0,
        timeoutEnabled: false
      },
      o2: {
        enabled: true,
        cardText: "Saida 2",
        cardOnText: "Ligada",
        cardOffText: "Desligada",
        cardOnClass: "bg-success text-white",
        cardOffClass: "bg-danger text-white",
        btnOnClass: "btn btn-lg btn-success mx-4 my-1",
        btnOnText: "Liga",
        btnOffClass: "btn btn-lg btn-danger mx-4 my-1",
        btnOffText: "Desliga",
        btnTglClass: "btn btn-lg btn-warning mx-4 my-1",
        btnTglText: "Inverter",
        enableSound: true,
        onSound: "",
        offSound: "",
        timeout: 0,
        timeoutEnabled: false
      },
      i1: {
        enabled: true,
        onText: "Ligado",
        onClass: "bg-success text-white",
        offText: "Desligado",
        offClass: "bg-danger text-white",
        enableSound: true,
        onSound: "",
        offSound: "",
      },
      i2: {
        enabled: true,
        onText: "Ligado",
        onClass: "bg-success text-white",
        offText: "Desligado",
        offClass: "bg-danger text-white",
        enableSound: true,
        onSound: "",
        offSound: "",
      },
    },
  }),
  methods: {
    setOutput(out, value, timeout) {
      let formData = new FormData();
      formData.append(`gpio${out}`, value);
      if (timeout) {
        formData.append(`timeout`, timeout);
      }
      if(out == 1 && this.config.o1.timeout > 0 && this.config.o1.timeoutEnabled){
        formData.append(`timeout`, this.config.o1.timeout);
      }
      if(out == 2 && this.config.o2.timeout > 0 && this.config.o2.timeoutEnabled){
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
            data.gpio1 ? this.config.o1.cardOnClass : this.config.o1.cardOffClass
          }`,
        });
      }
      if (data.gpio2 != null) {
        this.addToast({
          hideInToast: false,
          title: "Saída",
          body: `Saída 2 ${data.gpio2 ? "Ligada" : "Desligada"}`,
          add: new Date().getTime(),
          classTitle: `${
            data.gpio2 ? this.config.o1.cardOnClass : this.config.o2.cardOffClass
          }`,
        });
        this.g2 = data.gpio2;
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
          body: `Entrada 1 ${data.in1 ? "Ligada" : "Desligada"}`,
          add: new Date().getTime(),
          classTitle: `${
            data.in1 ? this.config.i1.onClass : this.config.i1.offClass
          }`,
        });
      }
      if (data.in2 != null) {
        this.i2 = data.in2;
        this.addToast({
          hideInToast: false,
          title: "Entrada",
          body: `Entrada 2 ${data.in2 ? "Ligada" : "Desligada"}`,
          add: new Date().getTime(),
          classTitle: `${
            data.in2 ? this.config.i2.onClass : this.config.i2.offClass
          }`,
        });
      }
    },
    wifiATT() {
      this.loadWifi();
    },
    loadCfg() {
      let cfg = localStorage.getItem("cfgESP");
      if (cfg) {
        this.config = JSON.parse(cfg);
      }
    },
    saveCFG() {
      localStorage.setItem("cfgESP", JSON.stringify(this.config));
    },
    loadData() {
      this.loadGpio();
      this.loadInput();
      this.loadWifi();
      this.loadCfg();
    },
  },
  mounted() {
    sseClient = new EventSource("http://192.168.88.31/events");
    // sseClient = new EventSource("http://10.10.10.145/events");
    // sseClient = new EventSource("/events");
    sseClient.onopen = function () {};
    sseClient.onerror = function () {};
    sseClient.addEventListener("output", this.output, false);
    sseClient.addEventListener("input", this.input, false);
    sseClient.addEventListener("wifi", this.wifiATT, false);
    this.loadData();
    document.title = "ESP01 IO";

    setInterval(() => {
      let now = new Date().getTime();
      this.toasts.forEach((element, index) => {
        if ((element.add + this.config.toastTime) < now) {
          this.toasts.splice(index, 1);
        }
      });
    }, 500);
  },
};
</script>
<style scoped>
</style>