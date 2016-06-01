/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package teacher;

/**
 *
 * @author victor
 */
public class Teacher extends Person {

    public Teacher() {
    }
    
    public int id() {
        return _id;
    }

    public void id( int id ) {
        this._id = id;
    }

    public String university() {
        return _university;
    }

    public void university( String university ) {
        this._university = university;
    }

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        Teacher t = new Teacher();
        t.first_name( "Víctor" );
        t.last_name( "Monserrat Villatoro" );
        t.age( 20 );
        t.id( 26 );
        t.university( "Universidad de Córdoba" );
        System.out.println( "El profesor " + t.first_name() + " "
                            + t.last_name() + " con edad " + t.age()
                            + " trabaja en la universidad "
                            + t.university() + " y tiene un id de profesor "
                            + t.id() + "." );
    }
    
    private int    _id;
    private String _university;
    
}
