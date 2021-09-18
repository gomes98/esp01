<template>
  <div class="card m-1">
    <div class="card-header">
      <div class="d-flex flex-row justify-content-between flex-wrap">
        Entrada {{pin}}
        <button
          @click="config.enableSound = !config.enableSound"
          class="btn btn-link btn-sm mx-1 p-0"
        >
          <img
            v-if="config.enableSound"
            src="@/assets/vu.svg"
            width="20"
          />
          <img v-else src="@/assets/vm.svg" width="20" />
        </button>
      </div>
    </div>
    <div class="card-body">
      <button
        class="btn btn-lg"
        :class="value == 0 ? config.onClass : config.offClass"
      >
        {{ value == 0 ? config.onText : config.offText }}
      </button>
    </div>
  </div>
</template>

<script>
export default {
  name: "inputCard",
  props: ["value", "config", "out", "pin"],
};
</script>

<style>
</style>