# Processador RISC em Pipeline usando SystemC
---

Este projeto foi desenvolvido por [Júlia Guilhermino](https://github.com/JuhGuilhermino) e [Ludmilla Rodrigues](https://github.com/Ludrodrigues) para disiciplina DIM0129 - Organização de Computadores, no ano de 2026. Ele consiste na implementação de um processador RISC organizado em um pipeline de 5 estados utilizando a bilioteca SystemC.

## Compilação
---
Escrever orientações aqui:

## To-do
---
Organização da implementação do projeto:

**Júlia Guilhermino**
- [ ] ULA
    - [ ] `/src/components/alu/alu.*`
    - [ ] `/tests/components/alu_tb.cpp`
- [ ] Banco de registradores
    - [ ] `/src/components/registers/registers.**`
    - [ ] `/tests/components/registers_tb.cpp`
- [ ] Memória de instrução 
    - [ ] `/src/components/instruction_memory/intruction_memeory.*`
    - [ ] `/tests/components/instruction_memory_tb.cpp`
- [ ] Memória de dados
    - [ ] `/src/components/data_memory/data_memory.*`
    - [ ] `/tests/components/data_memory_tb.cpp`
- [ ] Registradores de Pipeline
    - [ ] `/src/components/registers_pipeline/registers.*`
    - [ ] `/tests/components/registers_pipeline_tb.cpp`
- [ ] Conexão dos dados `/src/datapath/datapath.*`


**Ludmilla Rodrigues**
- [ ] Contador de programa 
    - [ ] `/src/components/pc/`
    - [ ] `/tests/components/pc_tb.cpp`
- [ ] MUX ``/src/components/mux/mux.*`
- [ ] Sing extend ``/src/components/sign_extend/sign_extend.*`
- [ ] Unidade de controle
    - [ ] `/src/control/pipeline/control_unit*`
    - [ ] `tests/control/pipeline_unit_control_tb.cpp`
- [ ] Conexão de sinais de controle `/src/integration/pipeline/datapath*`
- [ ] Construção do pipeline 
    - [ ] `/src/processor/processor.*`
    - [ ] `tests/processor_tb.cpp`