<template>
  <div>
    <div
      class="modal modalMM"
      id="myModal"
      style="display: block; overflow: auto; width: 100%"
    >
      <div class="modal-dialog modal-lg">
        <div class="modal-content">
          <!-- Modal Header -->
          <div class="modal-header d-inline-flex">
            <h4 class="modal-title">Configurações da Página</h4>
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
            <div class="row">
              <div class="col">
                <label for="timeourt">Tempo Toast: ms</label>
                <input
                  type="number"
                  class="form-control"
                  name="timeout"
                  id="timeout"
                  min="500"
                  max="60000"
                  step="500"
                  v-model.number="value.toastTime"
                />
              </div>
            </div>
            <div class="row">
              <div class="col">
                <label for="timeourt">Tempo para Inversão da Saída 1: ms</label>
                <input
                  type="number"
                  class="form-control"
                  name="timeout"
                  id="timeout"
                  min="500"
                  max="60000"
                  step="500"
                  v-model="value.o1.timeout"
                />
                <div class="form-check">
                  <input
                    class="form-check-input"
                    type="checkbox"
                    value=""
                    id="defaultCheck1"
                    v-model="value.o1.timeoutEnabled"
                  />
                  <label class="form-check-label" for="defaultCheck1">
                    Timer Ativo
                  </label>
                </div>
              </div>
              <div class="col">
                <label for="timeourt">Tempo para Inversão da Saída 2: ms </label>
                <input
                  type="number"
                  class="form-control"
                  name="timeout"
                  id="timeout"
                  min="500"
                  max="60000"
                  step="500"
                  v-model="value.o2.timeout"
                />
                <div class="form-check">
                  <input
                    class="form-check-input"
                    type="checkbox"
                    value=""
                    id="defaultCheck1"
                    v-model="value.o2.timeoutEnabled"
                  />
                  <label class="form-check-label" for="defaultCheck1">
                    Timer Ativo
                  </label>
                </div>
              </div>
            </div>
            <div class="card mt-1">
              <div class="card-header">Saida 1</div>
              <div class="card-body">
                <div class="row">
                  <div class="col">
                    <div class="form-group">
                      <label for="cardText1">Texto do Card</label>
                      <input
                        type="text"
                        class="form-control"
                        id="cardText1"
                        placeholder="Example input"
                        v-model="value.o1.cardText"
                      />
                    </div>
                  </div>
                </div>
                <div class="row">
                  <div class="col">
                    <div class="form-group">
                      <label for="cardOnClass1">Classe Ligado</label>
                      <input
                        type="text"
                        class="form-control"
                        id="cardOnClass1"
                        v-model="value.o1.cardOnClass"
                      />
                    </div>
                  </div>
                  <div class="col">
                    <div class="form-group">
                      <label for="cardOffClass1">Classe Desligado</label>
                      <input
                        type="text"
                        class="form-control"
                        id="cardOffClass1"
                        v-model="value.o1.cardOffClass"
                      />
                    </div>
                  </div>
                </div>
                <div class="row">
                  <div class="col">
                    <div class="form-group">
                      <label for="cardOnText1">Texto Ligado</label>
                      <input
                        type="text"
                        class="form-control"
                        id="cardOnText1"
                        v-model="value.o1.cardOnText"
                      />
                    </div>
                  </div>
                  <div class="col">
                    <div class="form-group">
                      <label for="cardOffText1">Texto Desligado</label>
                      <input
                        type="text"
                        class="form-control"
                        id="cardOffText1"
                        v-model="value.o1.cardOffText"
                      />
                    </div>
                  </div>
                </div>
                <div class="row">
                  <div class="col">
                    <div class="form-group">
                      <label for="btnOnText1">Nome do Botão Liga</label>
                      <input
                        type="text"
                        class="form-control"
                        id="btnOnText1"
                        v-model="value.o1.btnOnText"
                      />
                    </div>
                  </div>
                  <div class="col">
                    <div class="form-group">
                      <label for="btnOffText1">Nome do Botão Desliga</label>
                      <input
                        type="text"
                        class="form-control"
                        id="btnOffText1"
                        v-model="value.o1.btnOffText"
                      />
                    </div>
                  </div>
                  <div class="col">
                    <div class="form-group">
                      <label for="btntglText1">Nome do Botão Inverter</label>
                      <input
                        type="text"
                        class="form-control"
                        id="btnTglText1"
                        v-model="value.o1.btnTglText"
                      />
                    </div>
                  </div>
                </div>
                <div class="row">
                  <div class="col">
                    <div class="form-group">
                      <label for="btnOnClass1">Classe do Botão Liga</label>
                      <input
                        type="text"
                        class="form-control"
                        id="btnOnClass1"
                        v-model="value.o1.btnOnClass"
                      />
                    </div>
                  </div>
                  <div class="col">
                    <div class="form-group">
                      <label for="btnOffClass1">Classe do Botão Desliga</label>
                      <input
                        type="text"
                        class="form-control"
                        id="btnOffClass1"
                        v-model="value.o1.btnOffClass"
                      />
                    </div>
                  </div>
                  <div class="col">
                    <div class="form-group">
                      <label for="btnTglClass1">Classe do Botão Inverter</label>
                      <input
                        type="text"
                        class="form-control"
                        id="btnTglClass1"
                        v-model="value.o1.btnTglClass"
                      />
                    </div>
                  </div>
                </div>
                <div class="row">
                  <div class="col">
                    <div class="form-check">
                      <input
                        class="form-check-input"
                        type="checkbox"
                        value=""
                        id="defaultCheck1"
                        v-model="value.o1.enableSound"
                      />
                      <label class="form-check-label" for="defaultCheck1">
                        Som Ativado
                      </label>
                    </div>
                  </div>
                </div>
                <div class="row">
                  <div class="col">
                    <label for="cardText1">Som Ligado</label>
                    <input
                      type="text"
                      class="form-control"
                      id="cardText1"
                      placeholder="Url do audio"
                      v-model="value.o1.onSound"
                    />
                  </div>
                  <div class="col">
                    <label for="cardText1">Som Desligado</label>
                    <input
                      type="text"
                      class="form-control"
                      id="cardText1"
                      placeholder="Url do audio"
                      v-model="value.o1.offSound"
                    />
                  </div>
                </div>
              </div>
              <div class="card">
                <div class="card-header">Saida 2</div>
                <div class="card-body">
                  <div class="row">
                    <div class="col">
                      <div class="form-group">
                        <label for="cardText2">Texto do Card</label>
                        <input
                          type="text"
                          class="form-control"
                          id="cardText2"
                          placeholder="Example input"
                          v-model="value.o2.cardText"
                        />
                      </div>
                    </div>
                  </div>
                  <div class="row">
                    <div class="col">
                      <div class="form-group">
                        <label for="cardOnText2">Texto Ligado</label>
                        <input
                          type="text"
                          class="form-control"
                          id="cardOnText2"
                          v-model="value.o2.cardOnText"
                        />
                      </div>
                    </div>
                    <div class="col">
                      <div class="form-group">
                        <label for="cardOffText2">Texto Desligado</label>
                        <input
                          type="text"
                          class="form-control"
                          id="cardOffText2"
                          v-model="value.o2.cardOffText"
                        />
                      </div>
                    </div>
                  </div>
                  <div class="row">
                    <div class="col">
                      <div class="form-group">
                        <label for="cardOnClass2">Classe Ligado</label>
                        <input
                          type="text"
                          class="form-control"
                          id="cardOnClass2"
                          v-model="value.o2.cardOnClass"
                        />
                      </div>
                    </div>
                    <div class="col">
                      <div class="form-group">
                        <label for="cardOffClass2">Classe Ligado</label>
                        <input
                          type="text"
                          class="form-control"
                          id="cardOffClass2"
                          v-model="value.o2.cardOffClass"
                        />
                      </div>
                    </div>
                  </div>
                  <div class="row">
                    <div class="col">
                      <div class="form-group">
                        <label for="btnOnText2">Nome do Botão Liga</label>
                        <input
                          type="text"
                          class="form-control"
                          id="btnOnText2"
                          v-model="value.o2.btnOnText"
                        />
                      </div>
                    </div>
                    <div class="col">
                      <div class="form-group">
                        <label for="btnOffText2">Nome do Botão Desliga</label>
                        <input
                          type="text"
                          class="form-control"
                          id="btnOffText2"
                          v-model="value.o2.btnOffText"
                        />
                      </div>
                    </div>
                    <div class="col">
                      <div class="form-group">
                        <label for="btnTglText2">Nome do Botão Inverter</label>
                        <input
                          type="text"
                          class="form-control"
                          id="btnTglText2"
                          v-model="value.o2.btnTglText"
                        />
                      </div>
                    </div>
                  </div>
                  <div class="row">
                    <div class="col">
                      <div class="form-group">
                        <label for="btnOnClass2">Classe do Botão Liga</label>
                        <input
                          type="text"
                          class="form-control"
                          id="btnOnClass2"
                          v-model="value.o2.btnOnClass"
                        />
                      </div>
                    </div>
                    <div class="col">
                      <div class="form-group">
                        <label for="btnOffClass2"
                          >Classe do Botão Desliga</label
                        >
                        <input
                          type="text"
                          class="form-control"
                          id="btnOffClass2"
                          v-model="value.o2.btnOffClass"
                        />
                      </div>
                    </div>
                    <div class="col">
                      <div class="form-group">
                        <label for="btnTglClass2"
                          >Classe do Botão Inverter</label
                        >
                        <input
                          type="text2"
                          class="form-control"
                          id="btnTglClass"
                          v-model="value.o2.btnTglClass"
                        />
                      </div>
                    </div>
                  </div>
                  <div class="row">
                    <div class="col">
                      <div class="form-check">
                        <input
                          class="form-check-input"
                          type="checkbox"
                          value=""
                          id="defaultCheck1"
                          v-model="value.o2.enableSound"
                        />
                        <label class="form-check-label" for="defaultCheck1">
                          Som Ativado
                        </label>
                      </div>
                    </div>
                  </div>
                  <div class="row">
                    <div class="col">
                      <label for="cardText1">Som Ligado</label>
                      <input
                        type="text"
                        class="form-control"
                        id="cardText1"
                        placeholder="Url do audio"
                        v-model="value.o2.onSound"
                      />
                    </div>
                    <div class="col">
                      <label for="cardText1">Som Desligado</label>
                      <input
                        type="text"
                        class="form-control"
                        id="cardText1"
                        placeholder="Url do audio"
                        v-model="value.o2.offSound"
                      />
                    </div>
                  </div>
                </div>
              </div>
              <div class="card">
                <div class="card-header">Entrada 1</div>
                <div class="card-body">
                  <div class="row">
                    <div class="col">
                      <div class="form-group">
                        <label for="onText1">Texto Ligado</label>
                        <input
                          type="text"
                          class="form-control"
                          id="onText1"
                          v-model="value.i1.onText"
                        />
                      </div>
                    </div>
                    <div class="col">
                      <div class="form-group">
                        <label for="onClass1">Classe Ligado</label>
                        <input
                          type="text"
                          class="form-control"
                          id="onClass1"
                          v-model="value.i1.onClass"
                        />
                      </div>
                    </div>
                  </div>
                  <div class="row">
                    <div class="col">
                      <div class="form-group">
                        <label for="offText1">Texto Desligado</label>
                        <input
                          type="text"
                          class="form-control"
                          id="offText1"
                          v-model="value.i1.offText"
                        />
                      </div>
                    </div>
                    <div class="col">
                      <div class="form-group">
                        <label for="offClass1">Classe Desligado</label>
                        <input
                          type="text"
                          class="form-control"
                          id="offClass1"
                          v-model="value.i1.offClass"
                        />
                      </div>
                    </div>
                  </div>
                  <div class="row">
                    <div class="col">
                      <div class="form-check">
                        <input
                          class="form-check-input"
                          type="checkbox"
                          value=""
                          id="defaultCheck1"
                          v-model="value.i1.enableSound"
                        />
                        <label class="form-check-label" for="defaultCheck1">
                          Som Ativado
                        </label>
                      </div>
                    </div>
                  </div>
                  <div class="row">
                    <div class="col">
                      <label for="cardText1">Som Ligado</label>
                      <input
                        type="text"
                        class="form-control"
                        id="cardText1"
                        placeholder="Url do audio"
                        v-model="value.i1.onSound"
                      />
                    </div>
                    <div class="col">
                      <label for="cardText1">Som Desligado</label>
                      <input
                        type="text"
                        class="form-control"
                        id="cardText1"
                        placeholder="Url do audio"
                        v-model="value.i1.offSound"
                      />
                    </div>
                  </div>
                </div>
              </div>
              <div class="card">
                <div class="card-header">Entrada 2</div>
                <div class="card-body">
                  <div class="row">
                    <div class="col">
                      <div class="form-group">
                        <label for="onText2">Texto Ligado</label>
                        <input
                          type="text"
                          class="form-control"
                          id="onText2"
                          v-model="value.i2.onText"
                        />
                      </div>
                    </div>
                    <div class="col">
                      <div class="form-group">
                        <label for="onClass2">Classe Ligado</label>
                        <input
                          type="text"
                          class="form-control"
                          id="onClass2"
                          v-model="value.i2.onClass"
                        />
                      </div>
                    </div>
                  </div>
                  <div class="row">
                    <div class="col">
                      <div class="form-group">
                        <label for="offText2">Texto Desligado</label>
                        <input
                          type="text"
                          class="form-control"
                          id="offText2"
                          v-model="value.i2.offText"
                        />
                      </div>
                    </div>
                    <div class="col">
                      <div class="form-group">
                        <label for="offClass2">Classe Desligado</label>
                        <input
                          type="text"
                          class="form-control"
                          id="offClass2"
                          v-model="value.i2.offClass"
                        />
                      </div>
                    </div>
                  </div>
                  <div class="row">
                    <div class="col">
                      <div class="form-check">
                        <input
                          class="form-check-input"
                          type="checkbox"
                          value=""
                          id="defaultCheck1"
                          v-model="value.i2.enableSound"
                        />
                        <label class="form-check-label" for="defaultCheck1">
                          Som Ativado
                        </label>
                      </div>
                    </div>
                  </div>
                  <div class="row">
                    <div class="col">
                      <label for="cardText1">Som Ligado</label>
                      <input
                        type="text"
                        class="form-control"
                        id="cardText1"
                        placeholder="Url do audio"
                        v-model="value.i2.onSound"
                      />
                    </div>
                    <div class="col">
                      <label for="cardText1">Som Desligado</label>
                      <input
                        type="text"
                        class="form-control"
                        id="cardText1"
                        placeholder="Url do audio"
                        v-model="value.i2.offSound"
                      />
                    </div>
                  </div>
                </div>
              </div>
            </div>
          </div>
          <!-- Modal footer -->
          <div class="modal-footer">
            <button
              type="button"
              @click="limpar"
              class="btn btn-primary"
              data-dismiss="modal"
            >
              Restaurar Padrão
            </button>
            <button
              type="button"
              @click="$emit('close')"
              class="btn btn-danger"
              data-dismiss="modal"
            >
              Fechar
            </button>
            <button
              type="button"
              @click="salvar"
              class="btn btn-success"
              data-dismiss="modal"
            >
              Salvar
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
  props: ["value"],
  data: () => ({}),
  methods: {
    salvar() {
      this.$emit("save");
      this.$emit("close");
    },
    limpar() {
      localStorage.removeItem("cfgESP");
      alert("clique em atualizar para voltar ao padrão");
      this.$emit("close");
    },
  },
};
</script>

<style>
</style>