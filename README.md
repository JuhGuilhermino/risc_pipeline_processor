# Processador RISC em Pipeline usando SystemC 2
---

Este projeto foi desenvolvido por [Júlia Guilhermino](https://github.com/JuhGuilhermino) e [Ludmilla Rodrigues](https://github.com/Ludrodrigues) para disiciplina DIM0129 - Organização de Computadores, no ano de 2026. Ele consiste na implementação de um processador RISC organizado em um pipeline de 5 estados utilizando a bilioteca SystemC.

## Compilação
---
Escrever orientações aqui:

## To-do
---
Organização da implementação do projeto:

**Júlia Guilhermino**
- [x] ULA `/src/components/alu/*`
- [x] Banco de registradores `/src/components/registers/*`
- [x] Memória de instrução `/src/components/instruction_memory/*`
- [x] Memória de dados `/src/components/data_memory/*`
- [x] Registradores de Pipeline `/src/components/registers_pipeline/*`
- [ ] Conexão dos dados `/src/datapath/datapath.*`

**Ludmilla Rodrigues**
- [ ] Contador de programa `/src/components/pc/`
- [ ] MUX ``/src/components/mux/mux.*`
- [ ] Sing extend ``/src/components/sign_extend/sign_extend.*`
- [ ] Unidade de controle `/src/control/*`
- [ ] Conexão de sinais de controle `/src/datapath/datapath*`
- [ ] Construção do pipeline `/src/processor/processor.*`