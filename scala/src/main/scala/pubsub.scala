package eu.route20.hft.nos

import grizzled.slf4j.Logging
import org.zeromq.ZMQ
import scala.annotation.tailrec

object JeroMQ extends App with Logging {
  val ctx = ZMQ.context(1)
  val pub = ctx.socket(ZMQ.PUB)
  val sub = ctx.socket(ZMQ.SUB)

  info("starting up JeroMQ pubsub-system")
  sub.connect("tcp://169.254.5.233:5500")
  sub.connect("tcp://169.254.5.233:5501")
  sub.connect("tcp://169.254.5.233:5502")
  sub.subscribe("".getBytes)
  pub.bind("tcp://169.254.5.57:5600")
  recSend()
  sub.close()
  pub.close()
  ctx.term()
  info("JeroMQ down")

  @tailrec final def recSend(): Unit = {
    val msg = sub.recvStr()
    debug(msg)
    pub.send(msg)
    recSend()
  }
}
