<template>
  <div
    id="liveToast"
    class="toast"
    :class="`${data.hideInToast ? 'hide' : 'show'} ${data.classTitle}`"
    role="alert"
    aria-live="assertive"
    aria-atomic="true"
    data-delay="2000"
  >
    <div class="toast-header">
      <strong class="mr-auto">{{ data.title }}</strong>
      <button
        type="button"
        class="ml-2 mb-1 close"
        :class="data.classBody"
        data-dismiss="toast"
        aria-label="Close"
        @click="data.hideInToast = true"
      >
        <span aria-hidden="true">&times;</span>
      </button>
    </div>
    <div class="toast-body">{{ data.body }}</div>
  </div>
</template>

<script>
export default {
  name: "toast",
  props: ["value", "data", "number"],
};
</script>

<style>
</style>