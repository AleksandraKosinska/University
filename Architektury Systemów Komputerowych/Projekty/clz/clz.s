/*
 * UWAGA! W poniższym kodzie należy zawrzeć krótki opis metody rozwiązania
 *        zadania. Będzie on czytany przez sprawdzającego. Przed przystąpieniem
 *        do rozwiązywania zapoznaj się dokładnie z jego treścią. Poniżej należy
 *        wypełnić oświadczenie o samodzielnym wykonaniu zadania.
 *
 * Oświadczam, że zapoznałem(-am) się z regulaminem prowadzenia zajęć
 * i jestem świadomy(-a) konsekwencji niestosowania się do podanych tam zasad.
 *
 * Imię i nazwisko, numer indeksu: Aleksandra Kosińska, 317841
 */

        .text
        .globl  clz
        .type   clz, @function

/*
 * W moim rozwiązaniu używam następującej techniki: 
 *      1. Rozsmarowywuje jedynki tak aby zera które pozostaną to były tylko zera wiodące
 *      2. Neguje wszystkie bity (zera zmieniają się na jedynki)
 *      3. Zliczam ile mam zapolonych bitów w liczbie
 */

clz:
        /* Rozsmarowanie jedynek */
        movq    %rdi, %rax
        shrq    $1, %rax
        orq     %rax, %rdi

        movq    %rdi, %rax
        shrq    $2, %rax
        orq     %rax, %rdi

        movq    %rdi, %rax
        shrq    $4, %rax
        orq     %rax, %rdi

        movq    %rdi, %rax
        shrq    $8, %rax
        orq     %rax, %rdi

        movq    %rdi, %rax
        shrq    $16, %rax
        orq     %rax, %rdi

        movq    %rdi, %rax
        shrq    $32, %rax
        orq     %rax, %rdi

        /* Negacja bitow */
        notq    %rdi

        /* Zliczanie zapalonych bitow */
        movq    $0x5555555555555555, %rsi
        movq    %rdi, %rax
        shrq    $1, %rax
        andq    %rsi, %rax
        subq    %rax, %rdi

        movq    $0x3333333333333333, %rsi
        movq    %rdi, %rax
        shrq    $2, %rax
        andq    %rsi, %rax
        andq    %rsi, %rdi
        addq    %rax, %rdi

        movq    $0x0F0F0F0F0F0F0F0F, %rsi
        movq    %rdi, %rax
        shrq    $4, %rax
        addq    %rdi, %rax
        andq    %rsi, %rax

        movq    $0x0101010101010101, %rsi
        imulq   %rsi, %rax
        shrq    $56, %rax
        
        ret

        .size   clz, .-clz
