<template>
  <div
        id="liveToast"
        class="toast"
        :class="`${value.hideInToast ? 'hide' : 'show'} ${value.classTitle}`"
        role="alert"
        aria-live="assertive"
        aria-atomic="true"
        data-delay="2000"
      >
        <div class="toast-header">
          <strong class="mr-auto">{{value.title}}</strong>
          <button
            type="button"
            class="ml-2 mb-1 close"
            :class="value.classBody"
            data-dismiss="toast"
            aria-label="Close"
            @click="value.hideInToast = true"
          >
            <span aria-hidden="true">&times;</span>
          </button>
        </div>
        <div class="toast-body">{{value.body}}</div>
      </div>
</template>

<script>
export default {
    name: "toast",
    props: ['value']

}
</script>

<style>

</style>