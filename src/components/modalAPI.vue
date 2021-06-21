<template>
  <div>
    <div class="modal modalMM" id="myModal" style="display: block; overflow: auto; width: 100%;">
      <div class="modal-dialog">
        <div class="modal-content" >
          <!-- Modal Header -->
          <div class="modal-header d-inline-flex">
            <h4 class="modal-title">Manual da API</h4>
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
            <div class="card m-1">
              <div class="card-header">/wifi</div>
              <div class="card-body">
                <strong>POST</strong><br />
                <small>"Content-Type": "multipart/form-data"</small>
                <div class="card-body">
                  <pre>Paramentros <br>
                      ssid: nomedarede <br>
                      password: senha da rede
                  </pre>
                </div>
                <strong>GET</strong><br />
                <small>"Content-Type": "application/json"</small>
                <div class="card-body">
                  <pre>Retorno <br>
                      {
                        "ssid": "nomedarede",
                        "password": "senhadarede"
                      }
                  </pre>
                </div>
              </div>
            </div>
            <div class="card m-1">
              <div class="card-header">/gpio</div>
              <div class="card-body">
                <strong>POST</strong><br />
                <small>"Content-Type": "multipart/form-data"</small>
                <div class="card-body">
                  <pre>Paramentros <br>
                      gpio1: 1 para ligar ou 0 desligar ou t para inverter  <br>
                      gpio2: 1 para ligar ou 0 desligar ou t para inverter  <br>
                      timeout: tempo para inverter o estado enviado
                  </pre>
                </div>
                <strong>GET</strong><br />
                <small>"Content-Type": "application/json"</small>
                <div class="card-body">
                  <pre>Retorno <br>
                      {
                        "gpio1": 0,
                        "gpio2": 0
                      }
                  </pre>
                </div>
              </div>
            </div>
            <div class="card m-1">
              <div class="card-header">/input</div>
              <div class="card-body">
                <strong>GET</strong><br />
                <small>"Content-Type": "application/json"</small>
                <div class="card-body">
                  <pre>Retorno <br>
                      {
                        "in1": 1,
                        "in2": 1
                      }
                  </pre>
                </div>
              </div>
            </div>
            <div class="card m-1">
              <div class="card-header">/scan</div>
              <div class="card-body">
                <strong>GET</strong><br />
                <small>Redes disponivel</small><br>
                <small>"Content-Type": "application/json"</small>
                <div class="card-body">
                  <pre>Retorno <br>
                      [
                        {
                          "rssi": -48,
                          "ssid": "rede 2",
                          "bssid": "B4:43:26:11:C8:40",
                          "channel": 1,
                          "secure": 8,
                          "hidden": false
                        },
                        {
                          "rssi": -51,
                          "ssid": "rede1",
                          "bssid": "AC:84:C6:AC:A3:B8",
                          "channel": 1,
                          "secure": 4,
                          "hidden": false
                        }
                      ]
                  </pre>
                </div>
              </div>
            </div>
          </div>
            <div class="card m-1">
              <div class="card-header">/wstat</div>
              <div class="card-body">
                <strong>GET</strong><br />
                <small>Status do wifi</small><br>
                <small>"Content-Type": "application/json"</small>
                <div class="card-body">
                  <pre>Retorno <br>
                      {
                        "mac": "00:11:22:33:44:55",
                        "ip": "192.192.192.192",
                        "hostname": "nomenarede",
                        "SSID": "nomedowifi",
                        "RSSI": sinal,
                        "status": 3
                      }
                    Status:
                    0 = Idle
                    1 = Rede não encontrada
                    2 = Scan Completo
                    3 = Conectado
                    4 = Conexão Falhou (Senha)
                    5 = Conexão Perdida
                    6 = Desconectado
                  </pre>
                </div>
              </div>
            </div>
            <div class="card m-1">
              <div class="card-header">/event</div>
              <div class="card-body">
                <strong>SSE</strong><br />
                <small>Quando tem alguma alteração de status informa</small><br>
                <div class="card-body">
                  <pre>Eventos <br>
                      output: {gpio1: 0/1}
                      output: {gpio2: 0/1}
                      input : {in1: 0/1}
                      input : {in2: 0/1}
                  </pre>
                </div>
              </div>
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
  name: "modalApi",  
};
</script>

<style>
</style>