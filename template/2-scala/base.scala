abstract class AlgoApp extends App {
  import java.util.StringTokenizer

  var token = new StringTokenizer("")
  def read = {
  while (!token.hasMoreTokens())
    token = new StringTokenizer(readLine)
    token.nextToken()
  }
  def readInt = read.toInt
  def readLong = read.toLong
}
