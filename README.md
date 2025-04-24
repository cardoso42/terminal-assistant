# Terminal Assistant (C++)

Um assistente de terminal escrito em C++ que usa a [API do Deepseek](https://deepseek.com/) para responder perguntas e comandos do usuário com foco em terminal Linux.

## ✅ Funcionalidades

- Envia comandos e perguntas para a API da Deepseek
- Retorna a resposta no terminal
- Uso direto via linha de comando
- Leitura segura da chave da API via variável de ambiente

---

## 📦 Dependências

Você precisa das seguintes bibliotecas:

- [libcurl](https://curl.se/libcurl/) - Para fazer requisições HTTP
- [nlohmann/json](https://github.com/nlohmann/json) - Para manipulação de JSON

Em sistemas Debian/Ubuntu, você pode instalar com:

```bash
sudo apt install libcurl4-openssl-dev
```

E pode adicionar `nlohmann/json` ao seu projeto via vcpkg ou copiando o arquivo `json.hpp`.

---

## ⚙️ Compilação com CMake

Crie os diretórios e compile:

```bash
mkdir build && cd build
cmake ..
make
```

---

## 🧪 Uso

1. **Configure a variável de ambiente** com sua chave da API:

```bash
export DEEPSEEK_API_KEY="sua_chave_aqui"
```

Você pode colocar isso no seu `.bashrc`, `.zshrc` ou outro local carregado automaticamente.

2. **Execute o programa** com um comando como argumento:

```bash
./assistant "como listar arquivos ocultos no terminal?"
```
