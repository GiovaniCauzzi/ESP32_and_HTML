const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<style>
  html {
    text-align: center;
    text-decoration: none;
    font-size: 30px;
    margin: 2px;
    font-family: Helvetica;
    display: inline-block;
  }

  body {
    background-image: linear-gradient(to left, rgb(31, 29, 29), rgb(66, 65, 107));

  }

  h1 {
    color: rgb(217, 217, 223);
    font-family: 'Showcard Gothic';
  }

  h2 {
    color: rgb(217, 217, 223);
    font-family: 'Arial Black';
    font-size: 30px;
  }

  .button {
    background-color: #4CAF50;
    border: none;
    color: white;
    padding: 16px px;
    text-decoration: none;
    font-size: 30px;
    margin: 2px;
    cursor: pointer;
    height: 35px;
    width: 150px;
  }
</style>
</head>

<body>

  <h1>CONTROLE MOTOR</h1>
  <hr>
  <hr>
  <div>
    <div>
      <h2>Informar Velocidade Motor:</h2>
      <select id="VelocidadeMotorInformado">
        <option value="0">0%</option>
        <option value="50">50%</option>
        <option value="100">100%</option>
      </select>
      <button onclick="EnviarVelocidade()">Enviar Velocidade</button>
    </div>
    <div>
      <h2 id="StatusMotor"> Motor Desligado </h2>
      <p><a name="Motor"><button class="button" id="Botao" onclick="updateButton()">Ativar</button></a></p>
      <i class="fas fa-power-off"></i>
    </div>
    <div>
      <h2>Velocidade Motor:<h2>
          <p id="VelocidadeMotor"> 0 RPM </p>
    </div>
  </div>



  <script>

    setInterval(function () {
      // Call a function repetatively with 2 Second interval
      getData();
    }, 1000); //1000mSeconds update rate

    function getData() {
      var xhttp = new XMLHttpRequest();
      xhttp.onreadystatechange = function () {
        if (this.readyState == 4 && this.status == 200) {
          document.getElementById("VelocidadeMotor").innerHTML =
            this.responseText + " RPM";
        }
      };
      xhttp.open("GET", "readADC", true);
      xhttp.send();
    }

    function updateButton() {
      var xhttp = new XMLHttpRequest();
      xhttp.onreadystatechange = function () {
        if (this.readyState == 4 && this.status == 200) {
          if (this.responseText == "1") {
            document.getElementById("Botao").innerHTML = "Desativar";
            document.getElementById("StatusMotor").innerHTML = "Motor Ativado";
            document.getElementById("Botao").style.backgroundColor = "#B84F4F";
          }
          else {
            document.getElementById("Botao").innerHTML = "Ativar";
            document.getElementById("StatusMotor").innerHTML = "Motor Desativado";
            document.getElementById("Botao").style.backgroundColor = "#4CAF50";
          }
        }
      };
      xhttp.open("GET", "LigarDelisgarMotor", true);
      xhttp.send();
    }

    function EnviarVelocidade() {
      var xhttp = new XMLHttpRequest();
      xhttp.onreadystatechange = function () {
        if (this.readyState == 4 && this.status == 200) {
          document.getElementById("VelocidadeMotor").innerHTML =
            this.responseText + " RPM";
        }
      };
      var VelocidadeSelecionada = document.getElementById("VelocidadeMotorInformado").value
      if (VelocidadeSelecionada == "0") {
        xhttp.open("GET", "0%", true);
        xhttp.send();
      }
      if (VelocidadeSelecionada == "50") {
        xhttp.open("GET", "50%", true);
        xhttp.send();
      }
      if (VelocidadeSelecionada == "100") {
        xhttp.open("GET", "100%", true);
        xhttp.send();
      }


    }
  </script>
</body>

</html>
)=====";
