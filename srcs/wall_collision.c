/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_collision.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damachad <damachad@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 15:23:21 by damachad          #+#    #+#             */
/*   Updated: 2024/02/01 15:32:00 by damachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// ======Finding horizontal intersection ======
// 1. Finding the coordinate of A.  
//    If the ray is facing up      
//      A.y = rounded_down(Py/64) * (64) - 1;
//    If the ray is facing down
//      A.y = rounded_down(Py/64) * (64) + 64;




//    (In the picture, the ray is facing up, so we use
//    the first formula.  
//    A.y=rounded_down(224/64) * (64) - 1 = 191;
//    Now at this point, we can find out the grid 
//    coordinate of y.
//    However, we must decide whether A is part of 
//    the block above the line,
//    or the block below the line.  
//    Here, we chose to make A part of the block
//    above the line, that is why we subtract 1 from A.y.
//    So the grid coordinate of A.y is 191/64 = 2;

//    A.x = Px + (Py-A.y)/tan(ALPHA);
//    In the picture, (assume ALPHA is 60 degrees), 
//    A.x=96 + (224-191)/tan(60) = about 115;
//    The grid coordinate of A.x is 115/64 = 1;

//    So A is at grid (1,2) and we can check 
//    whether there is a wall on that grid.
//    There is no wall on (1,2) so the ray will be 
//    extended to C.

// 2. Finding Ya
//    If the ray is facing up      
//      Ya=-64;
//    If the ray is facing down
//      Ya=64;

// 3. Finding Xa
//    Xa = 64/tan(60) = 36;

// 4. We can get the coordinate of C as follows:
//    C.x=A.x+Xa = 115+36 = 151;
//    C.y=A.y+Ya = 191-64 = 127;
//    Convert this into grid coordinate by 
//    dividing each component with 64.  
//    The result is 
//    C.x = 151/64 = 2 (grid coordinate), 
//    C.y = 127/64 = 1 (grid coordinate) 
//    So the grid coordinate of C is (2, 1).  
//    (C programmer's note: Remember we always round down, 
//    this is especially true since
//    you can use right shift by 8 to divide by 64).

// 5. Grid (2,1) is checked.  
//    Again, there is no wall, so the ray is extended 
//    to D.  
   
// 6. We can get the coordinate of D as follows:
//    D.x=C.x+Xa = 151+36 = 187;
//    D.y=C.y+Ya = 127-64 = 63;
//    Convert this into grid coordinate by 
//    dividing each component with 64.  
//    The result is 
//    D.x = 187/64 = 2 (grid coordinate), 
//    D.y = 63/64 = 0 (grid coordinate) 
//    So the grid coordinate of D is (2, 0).  

// 6. Grid (2,0) is checked.  
//    There is a wall there, so the process stop.
