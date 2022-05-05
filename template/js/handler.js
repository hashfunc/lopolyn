function handleOnClickImageUpload() {
  const imageInput = document.getElementById("image-input");
  imageInput.click();
}

function handleOnUpload(files) {
  createImageBitmap(files[0]).then(preview);
}

function preview(bitmap) {
  const canvas = getPreviewCanvas();
  const ctx = canvas.getContext("2d");

  const ratio = bitmap.height / bitmap.width;
  const width = Math.min(800, bitmap.width);
  const height = width * ratio;

  canvas.width = width;
  canvas.height = height;

  ctx.drawImage(bitmap, 0, 0, width, height);
}

function getPreviewCanvas() {
  return document.querySelector("canvas#preview");
}
