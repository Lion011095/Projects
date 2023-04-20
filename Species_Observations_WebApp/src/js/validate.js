function validate(event) {
  // TODO - write custom validation logic to validate the longitude and latitude
  // values. The latitude value must be a number between -90 and 90; the
  // longitude value must be a number between -180 and 180. If either/both are
  // invalid, show the appropriate error message in the form, and stop the
  // form from being submitted. If both values are valid, allow the form to be
  // submitted.
  var latitude = document.querySelector("#observation-latitude").value;
  var longitude = document.querySelector("#observation-longitude").value;
  var longitudeError = document.createElement("span");
  longitudeError.innerText = " must be a valid Latitude (-180 to 180)";
  var latitudeError = document.createElement("span");
  latitudeError.innerText = " must be a valid Latitude (-90 to 90)";
  latitudeError.className = "error";
  longitudeError.className = "error";
  if (latitude === NaN || latitude > 90 || latitude < -90) {
    var latitudeLabel = document.querySelector("#latitude");
    latitudeLabel.appendChild(latitudeError);
    event.preventDefault();
  }
  if (longitude === NaN || longitude > 180 || longitude < -180) {
    var longitudeLabel = document.querySelector("#longitude");
    longitudeLabel.appendChild(longitudeError);
    event.preventDefault();
  }
  console.log(
    "TODO - validate the longitude, latitude values before submitting"
  );
}

// Wait for the window to load, then set up the submit event handler for the form.
window.onload = function () {
  const form = document.querySelector("form");
  form.onsubmit = validate;
};
