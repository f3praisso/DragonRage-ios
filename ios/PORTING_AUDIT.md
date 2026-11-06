# Dragon Rage — auditoria do port para iOS

Auditoria feita sobre o arquivo de origem `Tenkaichi3DecompAndroid-android-v0.9.0.zip` (1.380 entradas; aproximadamente 37,3 MB descompactados).

## Conclusão

O projeto já tem uma experiência experimental para macOS/Apple Silicon. Isso é uma base útil, mas **não é um versão iOS pronta**. O plano macOS registra testes nativos no Mac, enquanto o alvo iOS ainda precisa ser criado e validado com o SDK iPhoneOS.

## Componentes existentes que merecem reaproveitamento

- `port/tools/toolchain.py`: conhece a variante `mac64`, usa Homebrew LLVM e seleciona os caminhos de build.
- `port/tools/undefined.py`: fluxo de compilação por LLVM IR e transformação de ponteiros de 32 bits.
- `port/tools/macwin.py` e `port/tools/macwin/macwin.cpp`: transformação LLVM do modelo de janela de memória Apple.
- `port/src/port_addr.h`: conversão de endereços do jogo para a janela de memória Apple.
- `port/src/gs/gs_gpu.c`: renderer baseado na SDL GPU; o caminho Apple usa shaders MSL.
- `docs/port/macos_plan.md`: documentação e resultados experimentais do alvo macOS.

## Bloqueios específicos de iOS

1. **Memória e endereçamento:** `port/src/plat_mem.c` contém lógica Apple/macOS para reservar a janela de memória e iniciar o processo. iOS tem sandbox, ASLR e regras de mapeamento próprias; não assumir que o caminho macOS funciona no iPhone.
2. **Loader:** `android/app/src/main/cpp/loader.c` usa `android_dlopen_ext` e APIs Android. O iOS não carrega o `.so` Android; o motor deverá ser ligado ao executável Mach-O ou a uma biblioteca Mach-O compatível e iniciado por uma API C explícita.
3. **Build:** `port/tools/android.py` é específico de `aarch64-linux-android`, NDK e bibliotecas Android. A variante iOS deverá usar `arm64-apple-ios`, SDK iPhoneOS, SDL3 compilada para iOS e frameworks Apple.
4. **Plataforma:** auditar crash handling, arquivos e diretórios do sandbox, áudio, threads, sockets, entrada touch/controle e ciclo de vida/suspensão do app.
5. **Renderer:** validar SDL3 GPU com Metal no iOS; a existência do backend Metal no macOS não prova que a integração iOS já está pronta.
6. **BT4:** fica para depois do BT3. O host BT4 inclui JNI/ucontext Android e dependências gráficas Android próprias.

## Ordem recomendada

- [ ] Importar o código-fonte para este repositório, sem credenciais, chaves de assinatura ou dados de jogo.
- [ ] Criar variante `ios` no toolchain e compilar SDL3 para iOS.
- [ ] Criar um app iOS mínimo que abra uma janela SDL3/Metal em um dispositivo ou simulador compatível.
- [ ] Fazer spike isolado do modelo de memória e do transformador LLVM para iOS.
- [ ] Criar uma entrada C ABI para iniciar/parar BT3 sem o loader Android.
- [ ] Compilar e executar o motor BT3; depois integrar UI, controles e seleção dos arquivos do usuário.
- [ ] Só então empacotar e testar instalação via SideStore.
- [ ] Iniciar BT4 depois que BT3 estiver estável.

## Segurança ao importar o ZIP

O arquivo original inclui `android/app/dragonrage-test.jks`, um keystore de assinatura Android. **Não enviar esse arquivo ao GitHub.** Também não enviar ISOs, BIOS, saves privados, tokens, senhas ou outros segredos. O arquivo `.gitignore` do projeto já exclui vários diretórios de build e dados locais, mas a lista deve ser revisada antes do primeiro push.

## Estado real

O workflow `ios-toolchain-probe.yml` deste repositório já confirmou que o runner macOS consegue compilar um pequeno arquivo C para `arm64-apple-ios`. Esse teste não compila SDL3, o motor BT3, o app iOS nem gera IPA.
