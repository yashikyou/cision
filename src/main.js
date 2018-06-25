function main() {
  const canvas = document.querySelector('#c-canvas');
  const gl = canvas.getContext('webgl');

  if (!gl) {
    alert('your browser dont support webgl');
    return ;
  }

  gl.clearColor(0.0, 0.0, 0.0, 1.0);
  gl.clear(gl.COLOR_BUFFER_BIT);
}
