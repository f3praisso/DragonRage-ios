# Executar o primeiro teste de compilação iOS na nuvem

Este repositório ainda não possui um alvo CMake/Xcode completo para o motor BT3 no iOS.
Por isso, o workflow `iOS toolchain probe` faz somente um teste mínimo: verifica Xcode/iPhoneOS SDK e compila um arquivo C para `arm64-apple-ios15.0`, sem assinatura.

## Como executar

1. No GitHub, abra **Actions** → **iOS toolchain probe** → **Run workflow**.
2. Aguarde o job `iphoneos-arm64-probe`.
3. Se concluir, baixe o artefato `ios-arm64-toolchain-probe`.

## O que o resultado prova (e o que não prova)

- Sucesso prova que o runner macOS conseguiu usar o SDK iPhoneOS para compilar um objeto C arm64.
- Não prova que o motor BT3 compila, que a estratégia de memória é compatível com iOS, que Metal/SDL3 estão integrados, nem que existe um IPA instalável.
- Não há certificado, perfil de provisionamento, senha Apple ID ou segredo necessário neste teste.

O próximo passo após o probe é criar um alvo de build real para as dependências portáveis do motor e, separadamente, resolver a estratégia de memória/ABI antes de compilar o executável do jogo.
