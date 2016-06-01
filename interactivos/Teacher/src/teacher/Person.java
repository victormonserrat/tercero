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
public class Person {

    public Person() {
    }

    public String first_name() {
        return _firstName;
    }

    public void first_name( String firstName ) {
        this._firstName = firstName;
    }

    public String last_name() {
        return _lastName;
    }

    public void last_name( String lastName ) {
        this._lastName = lastName;
    }

    public int age() {
        return _age;
    }

    public void age( int age ) {
        this._age = age;
    }
    
    private String _firstName;
    private String _lastName;
    private int    _age;
    
}
