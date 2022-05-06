function handleOnClickImageUpload() {
  const imageInput = document.getElementById("image-input");
  imageInput.click();
}

function handleOnUpload(files) {
  createImageBitmap(files[0]).then(preview);
}

function preview(bitmap) {
  Module.API.BindCanvas("canvas#preview");

  setPreviewCanvas(bitmap.width, bitmap.height);

  const imageData = imageDataFromBitmap(bitmap);

  const buffer = Module.API.NewBuffer(bitmap.width * bitmap.height * 4);
  Module.HEAPU8.set(imageData.data, buffer);
  Module.API.Preview(buffer, imageData.width, imageData.height);
  Module.API.DeleteBuffer(buffer);
}

function setPreviewCanvas(width, height) {
  const previewCanvas = document.querySelector("canvas#preview");
  previewCanvas.width = width;
  previewCanvas.height = height;
}

function imageDataFromBitmap(bitmap) {
  const canvas = document.createElement("canvas");
  canvas.width = bitmap.width;
  canvas.height = bitmap.height;

  const ctx = canvas.getContext("2d");
  ctx.drawImage(bitmap, 0, 0);
  return ctx.getImageData(0, 0, bitmap.width, bitmap.height);
}
