<template>
  <div>
    <div class="card m-1">
      <div class="card-header">Rede</div>
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
            <button class="btn ml-auto p-2" @click="modalApi = true">API</button>
            <button class="btn ml-auto p-2" @click="modalCfg = true">
              Cfg
            </button>
            <button class="btn ml-auto p-2" @click="modalWifi = true">
              <img src="../src/assets/wifi.png" width="20" /> Selecionar
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
              {{ config.o1.cardText }} - {{g1 == 1 ? config.o1.cardOnText : config.o1.cardOffText }}
            </div>
            <div class="card-body">
              <div>
                <div class="d-flex flex-row justify-content-around flex-wrap">
                  <button :class="config.o1.btnOnClass" @click="sGpio1('1')">
                    {{ config.o1.btnOnText }}
                  </button>
                  <button :class="config.o1.btnOffClass" @click="sGpio1('0')">
                    {{ config.o1.btnOffText }}
                  </button>
                  <button :class="config.o1.btnTglClass" @click="sGpio1('t')">
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
              {{ config.o2.cardText }} - {{g2 == 1 ? config.o2.cardOnText : config.o2.cardOffText }}
            </div>
            <div class="card-body">
              <div>
                <div class="d-flex flex-row justify-content-around flex-wrap">
                  <button :class="config.o2.btnOnClass" @click="sGpio2('1')">
                    {{ config.o2.btnOnText }}
                  </button>
                  <button :class="config.o2.btnOffClass" @click="sGpio2('0')">
                    {{ config.o2.btnOffText }}
                  </button>
                  <button :class="config.o2.btnTglClass" @click="sGpio2('t')">
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
              <button
                class="btn btn-lg"
                :class="i1 == 0 ? config.i1.onClass : config.i1.offClass"
              >
                {{ i1 == 0 ? config.i1.onText : config.i1.offText }}
              </button>
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
    <Modal v-if="modalWifi" @close="modalWifi = false" />
    <ModalAPI v-if="modalApi" @close="modalApi = false" />
    <ModalCFG
      v-if="modalCfg"
      @close="modalCfg = false"
      v-model="config"
      @save="saveCFG"
    />
  </div>
</template>

<script>
import Modal from "./components/modal.vue";
import ModalAPI from "./components/modalAPI.vue";
import ModalCFG from "./components/modalCfg.vue";
import "./assets/bootstrap.min.css";
let sseClient;
export default {
  name: "App",
  components: {
    Modal,
    ModalAPI,
    ModalCFG,
  },
  data: () => ({
    modalWifi: false,
    modalApi: false,
    modalCfg: false,
    g1: 0,
    g2: 0,
    i1: 0,
    i2: 0,
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
      o1: {
        enabled: true,
        cardText: "Saida 1",
        cardOnText: 'Ligada',
        cardOffText: 'Desligada',
        cardOnClass: "bg-success text-white",
        cardOffClass: "bg-danger text-white",
        btnOnClass: "btn btn-lg btn-success mx-4 my-1",
        btnOnText: "Liga",
        btnOffClass: "btn btn-lg btn-danger mx-4 my-1",
        btnOffText: "Desliga",
        btnTglClass: "btn btn-lg btn-warning mx-4 my-1",
        btnTglText: "Inverter",
      },
      o2: {
        enabled: true,
        cardText: "Saida 2",
        cardOnText: 'Ligada',
        cardOffText: 'Desligada',
        cardOnClass: "bg-success text-white",
        cardOffClass: "bg-danger text-white",
        btnOnClass: "btn btn-lg btn-success mx-4 my-1",
        btnOnText: "Liga",
        btnOffClass: "btn btn-lg btn-danger mx-4 my-1",
        btnOffText: "Desliga",
        btnTglClass: "btn btn-lg btn-warning mx-4 my-1",
        btnTglText: "Inverter",
      },
      i1: {
        enabled: true,
        onText: "Ligado",
        onClass: "bg-success text-white",
        offText: "Desligado",
        offClass: "bg-danger text-white",
      },
      i2: {
        enabled: true,
        onText: "Ligado",
        onClass: "bg-success text-white",
        offText: "Desligado",
        offClass: "bg-danger text-white",
      },
    },
  }),
  methods: {
    sGpio1(value) {
      let formData = new FormData();
      formData.append("gpio1", value);
      this.$http
        .post(`/gpio`, formData, {
          headers: {
            "Content-Type": "multipart/form-data",
          },
        })
        .then(() => {});
    },
    sGpio2(value) {
      let formData = new FormData();
      formData.append("gpio2", value);
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
      }
      if (data.gpio2 != null) {
        this.g2 = data.gpio2;
      }
    },
    input(value) {
      let data = JSON.parse(value.data);
      if (data.in1 != null) {
        this.i1 = data.in1;
      }
      if (data.in2 != null) {
        this.i2 = data.in2;
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
  },
  mounted() {
    // sseClient = new EventSource("http://192.168.88.33/events");
    sseClient = new EventSource("/events");
    sseClient.onopen = function () {};
    sseClient.onerror = function () {};
    sseClient.addEventListener("output", this.output, false);
    sseClient.addEventListener("input", this.input, false);
    sseClient.addEventListener("wifi", this.wifiATT, false);

    this.loadGpio();
    this.loadInput();
    this.loadWifi();
    this.loadCfg();

    document.title = "ESP01 IO";
  },
};
</script>
<style scoped>
</style>