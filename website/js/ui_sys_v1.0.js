const _ = require("lodash");
//const validarCpf = require("validar-cpf");
const express = require("express");
const orm = require("orm");

const PORT = 8080;
const DB_USER = "u185329633_rlb";
const DB_PASS = "admindb";
const DB_HOST = "127.0.0.1:3306";
const DB_NAME = "u185329633_rlb";

const app = express();

app.use(express.json());
app.use(
  orm.express(`mysql://${DB_USER}:${DB_PASS}@${DB_HOST}/${DB_NAME}`, {
    define: function(db, models) {
      models.usuario = db.define("usuario", {
        nome: String,
        cpf: String,
        idade: Number,
        peso: Number,
        altura: Number,
        imc: Number
      });
    }
  })
);

// GET - Retornar todos os usuarios ou buscar por nome
app.get("/usuarios", function(req, res) {
  const { nome } = req.query;
  if (nome) {
    req.models.usuario.find(
      { nome: orm.like(`%${nome}%`) },
      (err, usuarios) => {
        res.send(usuarios);
      }
    );
  } else {
    req.models.usuario.all((err, usuarios) => {
      res.send(usuarios);
    });
  }
});

// GET - Retornar um usuario pelo CPF
app.get("/usuario/:cpf", function(req, res) {
  const { cpf } = req.params;
  if (cpf) {
    req.models.usuario.find({ cpf }, (err, usuarios) => {
      if (_.isEmpty(usuarios)) {
        return res.status(404).send("Not found");
      }
      res.send(_.first(usuarios));
    });
  }
});

// POST - criar um novo usuario com seu IMC calculado automaticamente
app.post("/usuario", function(req, res) {
  const { nome, cpf, idade, altura, peso } = req.body;
  if (!cpf || !validarCpf(cpf)) {
    return res.status(400).send("CPF invalido");
  }
  if (!idade || !_.isNumber(idade)) {
    return res.status(400).send("Idade invalida");
  }
  if (!altura || !_.isNumber(altura)) {
    return res.status(400).send("Altura invalida");
  }
  if (!peso || !_.isNumber(peso)) {
    return res.status(400).send("Peso invalido");
  }
  const imc = peso / (altura * altura);
  const usuario = { nome, cpf, idade, altura, peso, imc };

  req.models.usuario.create(usuario, (err, usuario) => {
    if (err) {
      return res.status(400).send();
    }
    res.send(usuario);
  });
}); 

// DELETE - deletar um usuario pelo CPF
app.delete("/usuario/:cpf", function(req, res) {
  const { cpf } = req.params;
  if (cpf) {
    req.models.usuario.find({ cpf }, (err, usuarios) => {
      if (_.isEmpty(usuarios)) {
        return res.status(404).send("Not found");
      }

      _.first(usuarios).remove(function(err) {
        if (err) {
          return res.status(500).send();
        }
        res.status(204).send();
      });
    });
  }
});

app.listen(PORT, () => {
  console.log(`Listening at port ${PORT}`);
});