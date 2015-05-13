/* En este test vamos a ver que Scala es un lenguaje de programacion de tipado
 * estatico.
 * Para ello vamos a ver como Scala no compila porque al verificar los tipos de
 * las variables vera que no son compatibles y nos lanzara un error de tipo.
 */

object Main extends App {
   def algo() : Int = {
      var a:Int = 0
      var b:String = "33"
      a = a + b
      return a
   }
}
