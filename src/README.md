Neste documento reflectiranse que opcións foron valoradas, cales implementadas e por que das suxeridas no guión da práctica.

* Xeracíon da solución inicial greedy.

Esta mellora foi contemplada nun inicio e implementada de forma que se crea unha solución inicial moito mellor xa en primeira instancia polo que,
 a solución acadada é atopada nas primeiras iteracións do bulce.
  Esta foi a primeira mellora implementada e causou un gran impacto. Se ben xuntándoa con melloras posteriores dito impacto se ve reducido,
 sigue sendo importante no rendemento xeral do algoritmo.

* Modificación do operador de veciñanza

Modificouse o operador de xeración de veciñanza engadindo unha ponderación, desta forma os pares máis xerados vense penalizados. Isto permítenos obter unha mostra máis heteroxénea e evitar os posibles bloqueos en mínimos locais. Esta modificación vese combinada cun reinicio voraz para a mellor resultado.

* Emprego de oscilación estratéxica na reinicialización

desta forma nunhas iteracións xérase unha nova solución actual de forma voraz buscando a mellor aproximación e, noutras iteracións selecciónase unha solución dun array de solucións de forma que poidamos evitar os mínimos mencionados anteriormente pero ao mesmo tempo garanticemos que a solución seleccionada para evitar dito mínimo segue sendo boa.

* Modificación da función de cálculo de custo

básicamente modificouse a función co obxectivo de gañar velocidade e conseguir un algoritmo rápido.

* Outras modificacións
Valorouse non reinicializar a lista tabú -> comprobouse que non existía ningún tipo de mellora senón que, nalgúns casos ocasionaba empeoramentos.



Considerouse asimesmo engadir outro parámetro de penalización na busca voraz tendo en conta as posicións dos distintos elementos na matriz para comprobar se algunha zona quedaba de forma reiterada pouco usada e potenciar o seu uso. Neste caso non se implementou debido a que, vistos os resultados dos compañeiros a ganancia en distancia non ía ser suficiente como para compensar o custo engadido en tempo deste procesado.
