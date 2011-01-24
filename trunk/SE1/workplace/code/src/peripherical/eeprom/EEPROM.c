/*
 * 1024 * 1 byte
 * Write 1 Byte
 * Write 1 Page = 16 Bytes
 * 64 Pages
 * TOTAL:
 * [4 Bytes] TOTAL DISTANCE    //• totalização de distância percorrida pelo veículo, em quilómetros;
 * [4 Bytes] TOTAL USAGE TIME  //• totalização de tempo de utilização, em horas.
 * CURRENT:  
 * [7 Bytes]START             //• data/hora de início do percurso;
 * [4 Bytes]DISTANCE          //• distância percorrida;
 * [4 Bytes]TIME              //• tempo despendido no percurso;
 * [4 Bytes]STOPTIME          //• tempo parado - soma dos períodos de tempo em que o veículo esteve parado.
 * [4 Bytes]MAX SPEED         //• velocidade máxima – a velocidade máxima instantânea atingida pelo veículo;
 * -----------------------------------------------------------------------------
 * 
 * */
 
 
