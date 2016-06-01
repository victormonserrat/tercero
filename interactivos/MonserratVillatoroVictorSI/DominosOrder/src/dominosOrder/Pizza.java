/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package dominosOrder;

/**
 *
 * @author victor
 */
public class Pizza {
    public Pizza() {
        _number = 1;
        _size = 0;
        _dough = 1;
        _sauce = 0;
        _olives = false;
        _anchovies = false;
        _tuna = false;
        _bacon = false;
        _onion = false;
        _mushrooms = false;
        _york = false;
        _ham = false;
        _corn = false;
        _pepperoni = false;
        _pepper = false;
        _pineapple = false;
        _chicken = false;
        _beef = false;
        _tomato = false;
        _caramel = false;
    }

    public int getNumber() {
        return _number;
    }

    public void setNumber(int _number) {
        this._number = _number;
    }

    public int getSize() {
        return _size;
    }

    public void setSize(int _size) {
        this._size = _size;
    }

    public int getDough() {
        return _dough;
    }

    public void setDough(int _dough) {
        this._dough = _dough;
    }

    public int getSauce() {
        return _sauce;
    }

    public void setSauce(int _sauce) {
        this._sauce = _sauce;
    }

    public boolean isOlives() {
        return _olives;
    }

    public void setOlives(boolean _olives) {
        this._olives = _olives;
    }

    public boolean isAnchovies() {
        return _anchovies;
    }

    public void setAnchovies(boolean _anchovies) {
        this._anchovies = _anchovies;
    }

    public boolean isTuna() {
        return _tuna;
    }

    public void setTuna(boolean _tuna) {
        this._tuna = _tuna;
    }

    public boolean isBacon() {
        return _bacon;
    }

    public void setBacon(boolean _bacon) {
        this._bacon = _bacon;
    }

    public boolean isOnion() {
        return _onion;
    }

    public void setOnion(boolean _onion) {
        this._onion = _onion;
    }

    public boolean isMushrooms() {
        return _mushrooms;
    }

    public void setMushrooms(boolean _mushrooms) {
        this._mushrooms = _mushrooms;
    }

    public boolean isYork() {
        return _york;
    }

    public void setYork(boolean _york) {
        this._york = _york;
    }

    public boolean isHam() {
        return _ham;
    }

    public void setHam(boolean _ham) {
        this._ham = _ham;
    }

    public boolean isCorn() {
        return _corn;
    }

    public void setCorn(boolean _corn) {
        this._corn = _corn;
    }

    public boolean isPepperoni() {
        return _pepperoni;
    }

    public void setPepperoni(boolean _pepperoni) {
        this._pepperoni = _pepperoni;
    }

    public boolean isPepper() {
        return _pepper;
    }

    public void setPepper(boolean _pepper) {
        this._pepper = _pepper;
    }

    public boolean isPineapple() {
        return _pineapple;
    }

    public void setPineapple(boolean _pineapple) {
        this._pineapple = _pineapple;
    }

    public boolean isChicken() {
        return _chicken;
    }

    public void setChicken(boolean _chicken) {
        this._chicken = _chicken;
    }

    public boolean isBeef() {
        return _beef;
    }

    public void setBeef(boolean _beef) {
        this._beef = _beef;
    }

    public boolean isTomato() {
        return _tomato;
    }

    public void setTomato(boolean _tomato) {
        this._tomato = _tomato;
    }

    public boolean isCaramel() {
        return _caramel;
    }

    public void setCaramel(boolean _caramel) {
        this._caramel = _caramel;
    }
    
    private int _number;
    private int _size;
    private int _dough;
    private int _sauce;
    private boolean _olives;
    private boolean _anchovies;
    private boolean _tuna;
    private boolean _bacon;
    private boolean _onion;
    private boolean _mushrooms;
    private boolean _york;
    private boolean _ham;
    private boolean _corn;
    private boolean _pepperoni;
    private boolean _pepper;
    private boolean _pineapple;
    private boolean _chicken;
    private boolean _beef;
    private boolean _tomato;
    private boolean _caramel;
    private String _name;

    public String getName() {
        return _name;
    }

    public void setName(String _name) {
        this._name = _name;
    }
}
