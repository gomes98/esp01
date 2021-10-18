<template>
  <div class="card m-1">
    <div
      class="card-header"
      :class="value == 1 ? config.cardOnClass : config.cardOffClass"
    >
      <div class="d-flex flex-row justify-content-between flex-wrap">
        {{ config.cardText }} -
        {{ value == 1 ? config.cardOnText : config.cardOffText }}
        <button
          @click="config.enableSound = !config.enableSound"
          class="btn btn-link btn-sm mx-1 p-0"
        >
          <img v-if="config.enableSound" src="@/assets/vu.svg" width="20" />
          <img v-else src="@/assets/vm.svg" width="20" />
        </button>
        <button
          @click="config.timeoutEnabled = !config.timeoutEnabled"
          class="btn btn-link btn-sm m-0 p-0"
        >
          <img v-if="config.timeoutEnabled" src="@/assets/hgs.svg" width="20" />
          <img v-else src="@/assets/hg.svg" width="20" />
        </button>
      </div>
    </div>
    <div class="card-body">
      <div>
        <div class="d-flex flex-row justify-content-around flex-wrap">
          <button :class="config.btnOnClass" @click="out(pin, 't')">
            {{ config.btnOnText }}
          </button>
          <button :class="config.btnOffClass" @click="out(pin, 't')">
            {{ config.btnOffText }}
          </button>
          <button :class="config.btnTglClass" @click="out(pin, 't')">
            {{ config.btnTglText }}
          </button>
        </div>
      </div>
    </div>
  </div>
</template>

<script>
export default {
  name: "outputCard",
  props: ["value", "config", "out", "pin"],
};
</script>

<style>
</style>