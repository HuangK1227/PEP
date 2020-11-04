// Part 2 about finding a single tour for a board using the Warnsdorf Rule
//=========================================================================

// !!! Copy any function you need from file knight1.scala !!!
//
// If you need any auxiliary function, feel free to 
// implement it, but do not make any changes to the
// templates below.

type Pos = (Int, Int)    // a position on a chessboard 
type Path = List[Pos]    // a path...a list of positions

def is_legal(dim: Int, path: Path, x: Pos) : Boolean ={
  if(x._1 >= 0 && x._1 < dim && x._2 >= 0 && x._2 < dim && !path.contains(x)){
    true
  }else{
    false
  }  
} 

def legal_moves(dim: Int, path: Path, x: Pos) : List[Pos] = {
  List((x._1 + 1, x._2 + 2),
       (x._1 + 2, x._2 + 1), 
       (x._1 + 2, x._2 - 1), 
       (x._1 + 1, x._2 - 2), 
       (x._1 - 1, x._2 - 2), 
       (x._1 - 2, x._2 - 1), 
       (x._1 - 2, x._2 + 1), 
       (x._1 - 1, x._2 + 2)).filter(x => is_legal(dim, path,x))
}

def first(xs: List[Pos], f: Pos => Option[Path]) : Option[Path] = { 
 if (xs == Nil) None 
 else {  
 val temp = f(xs.head) 
 if ( temp.isDefined) temp 
   else first(xs.drop(1), f) 
   } 
 }

 def is_legal_closed(dim: Int, path: Path, x: Pos) : Boolean ={
  if(x._1 >= 0 && x._1 < dim && x._2 >= 0 && x._2 < dim && path.contains(x)){
    true
  }else{
    false
  }  
}  

def legal_moves_closed(dim: Int, path: Path, x: Pos) : List[Pos] = {
  List((x._1 + 1, x._2 + 2),
       (x._1 + 2, x._2 + 1), 
       (x._1 + 2, x._2 - 1), 
       (x._1 + 1, x._2 - 2), 
       (x._1 - 1, x._2 - 2), 
       (x._1 - 2, x._2 - 1), 
       (x._1 - 2, x._2 + 1), 
       (x._1 - 1, x._2 + 2)).filter(x => is_legal_closed(dim, path,x))
}

//(6) Complete the function that calculates a list of onward
//    moves like in (2) but orders them according to Warnsdorf’s 
//    rule. That means moves with the fewest legal onward moves 
//    should come first.


def ordered_moves(dim: Int, path: Path, x: Pos) : List[Pos] = {
  legal_moves(dim, path, x).sortBy(legal_moves(dim, path, _).length)
}

//(7) Complete the function that searches for a single *closed* 
//    tour using the ordered_moves function from (6). This
//    function will be tested on a 6 x 6 board. 



def first_closed_tour_heuristic(dim: Int, path: Path) : Option[Path] = {
  if(path.length == dim * dim){
    if(legal_moves_closed(dim, path, path.head).contains(path.last)){
      Option(path)
    }
    else{
      None
    }
  }
  else{
    val recursive = (h:Pos) => first_closed_tour_heuristic(dim, h::path)
    first(ordered_moves(dim, path, path.head), recursive)
  }
}

//(8) Same as (7) but searches for *non-closed* tours. This 
//    version of the function will be called with dimensions of 
//    up to 30 * 30.

def first_tour_heuristic(dim: Int, path: Path) : Option[Path] = {
  if(path.length == dim * dim){
    if(legal_moves(dim, path, path.head).contains(path.last)){
      Option(path)
    }
    else{
      None
    }
  }
  else{
    val recursive = (h:Pos) => first_tour_heuristic(dim, h::path)
    first(ordered_moves(dim, path, path.head), recursive)
  }
}

println(first_tour_heuristic(30, List((0,0))))
