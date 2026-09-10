# PSE em Ação — Sistema de Apoio à Vacinação Escolar

Sistema em linguagem C, executado em terminal, para apoiar o planejamento, registro e acompanhamento de ações de vacinação escolar realizadas no âmbito do **Programa Saúde na Escola (PSE)**.

Atividade Extensionista Prática (AEP) — 2º Semestre de 2026
Curso: ESOFT2S

## Integrantes

- Matheus Guelles Doná
- João Artur Prado Martins
- Nicholas Tadei Esteves

## Descrição do projeto

O Programa Saúde na Escola (PSE) inclui, entre suas ações prioritárias, a verificação da situação vacinal de estudantes da rede pública. Apesar dos avanços recentes na integração entre saúde e educação, a execução dessas ações ainda enfrenta desafios de comunicação, planejamento e acompanhamento, muitas vezes registradas em anotações e planilhas dispersas.

Este projeto propõe uma aplicação simples em C, executada em terminal, capaz de:

- Cadastrar ações de vacinação (escola, data prevista, público-alvo, responsável, quantidade prevista);
- Listar e pesquisar ações por código, escola ou tema;
- Atualizar a situação de uma ação (planejada, realizada ou cancelada);
- Gerar um resumo geral com quantidade de ações por situação e percentual de participação.

O sistema **não coleta nem armazena dados clínicos individuais** de estudantes (nome, diagnóstico, prontuário), trabalhando apenas com informações coletivas e fictícias sobre as ações planejadas, sem substituir o trabalho de profissionais de saúde.

### Requisitos funcionais (resumo)

| Código | Descrição |
|---|---|
| RF01 | Cadastro de ação de vacinação |
| RF02 | Listagem de todas as ações cadastradas |
| RF03 | Pesquisa de ações por código, escola ou tema |
| RF04 | Atualização da situação da ação e registro de participantes efetivos |
| RF05 | Geração de resumo geral (ações e percentual de participação) |
| RF06 | Validação de entradas (códigos duplicados, campos vazios, valores inválidos) |

### Requisitos não funcionais (resumo)

- Execução em terminal, sem interface gráfica, banco de dados ou bibliotecas externas avançadas;
- Dados mantidos em memória (vetores/structs) durante a execução;
- Nenhum dado clínico individual armazenado;
- Código modularizado em funções, sem concentrar lógica na `main`;
- Mensagens claras de confirmação e erro.

## Organização das pastas

```
.
├── README.md
├── docs/
│   ├── AEP_Etapa1_PSE_Vacinacao_formatado.docx   # Documento escrito da Etapa 1 (formatação ABNT)
│   ├── requisitos/                                # Requisitos funcionais e não funcionais
│   ├── diagramas/                                 # Fluxogramas (menu principal e cadastro de ação)
│   └── pseudocodigo/                              # Pseudocódigos do menu principal e do cadastro
├── src/                                            # Código-fonte em C (Etapa 2)
└── manual/                                         # Manual do usuário e capturas de tela (Etapa 2)
```

## Etapas e planejamento de sprints

**Etapa 1 — Documento escrito (semanas 1 a 6):** contextualização, problema de pesquisa, objetivos, justificativa, requisitos, fluxogramas, pseudocódigos, planejamento de sprints e criação/organização do repositório GitHub. *(Status: concluída)*

**Etapa 2 — Implementação e apresentação (semanas 7 a 15):** implementação em C de todas as funcionalidades (cadastro, listagem, pesquisa, atualização e resumo), testes, diagrama de casos de uso, manual do usuário e apresentação em vídeo. *(Status: em andamento)*

## Sobre o documento escrito

O documento da Etapa 1 (`docs/AEP_Etapa1_PSE_Vacinacao_formatado.docx`) segue as normas ABNT: fonte Times New Roman 12, espaçamento entrelinhas 1,5, recuo de primeira linha, margens de 3 cm (esquerda/superior) e 2 cm (direita/inferior), numeração de página e referências em ordem alfabética.

## Referências

As referências bibliográficas completas utilizadas na fundamentação do projeto (BRASIL, 2007; Portaria Interministerial nº 1.055/2017; BVS/MS; DATASUS/PNI; Instituto Butantan; Ministério da Educação; Agência Gov; SOUSA, ESPERIDIÃO e MEDINA, 2017) estão disponíveis no documento completo em `docs/AEP_Etapa1_PSE_Vacinacao_formatado.docx`.
