abstract class AlgoApp extends App {
  import java.util.StringTokenizer
  
  var token = new StringTokenizer("")
  def next = {
    while (!token.hasMoreTokens())
      token = new StringTokenizer(readLine)
    token.nextToken()
  }
  def nextInt = next.toInt
  def nextLong = next.toLong
}
