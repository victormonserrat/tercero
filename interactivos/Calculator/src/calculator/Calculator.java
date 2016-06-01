/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package calculator;

import javax.script.ScriptEngineManager;
import javax.script.ScriptEngine;
import javax.script.ScriptException;
import javax.swing.JTextField;

/**
 *
 * @author victor
 */
public class Calculator extends javax.swing.JFrame {

    /**
     * Creates new form Calculator
     */
    public Calculator() {
        initComponents();
    }

    /**
     * This method is called from within the constructor to initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is always
     * regenerated by the Form Editor.
     */
    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        _textResult = new javax.swing.JTextField();
        _buttonOP = new javax.swing.JButton();
        _buttonCP = new javax.swing.JButton();
        _buttonDEL = new javax.swing.JButton();
        _buttonAC = new javax.swing.JButton();
        _button7 = new javax.swing.JButton();
        _button8 = new javax.swing.JButton();
        _button9 = new javax.swing.JButton();
        _buttonANS = new javax.swing.JButton();
        _buttonMod = new javax.swing.JButton();
        _button4 = new javax.swing.JButton();
        _button5 = new javax.swing.JButton();
        _button6 = new javax.swing.JButton();
        _buttonPro = new javax.swing.JButton();
        _buttonDiv = new javax.swing.JButton();
        _button1 = new javax.swing.JButton();
        _button2 = new javax.swing.JButton();
        _button3 = new javax.swing.JButton();
        _buttonSum = new javax.swing.JButton();
        _buttonSub = new javax.swing.JButton();
        _button0 = new javax.swing.JButton();
        _buttonDot = new javax.swing.JButton();
        _buttonExp = new javax.swing.JButton();
        _buttonResult = new javax.swing.JButton();

        setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);

        _textResult.setEditable(false);
        _textResult.setBackground(java.awt.Color.gray);
        _textResult.setFont(new java.awt.Font("Droid Sans Mono", 0, 24)); // NOI18N
        _textResult.setForeground(java.awt.Color.lightGray);

        _buttonOP.setBackground(java.awt.Color.gray);
        _buttonOP.setFont(new java.awt.Font("Droid Sans Mono", 0, 15)); // NOI18N
        _buttonOP.setForeground(java.awt.Color.darkGray);
        _buttonOP.setText("(");
        _buttonOP.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                write(evt);
            }
        });

        _buttonCP.setBackground(java.awt.Color.gray);
        _buttonCP.setFont(new java.awt.Font("Droid Sans Mono", 0, 15)); // NOI18N
        _buttonCP.setForeground(java.awt.Color.darkGray);
        _buttonCP.setText(")");
        _buttonCP.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                write(evt);
            }
        });

        _buttonDEL.setBackground(java.awt.Color.orange);
        _buttonDEL.setFont(new java.awt.Font("Droid Sans Mono", 0, 15)); // NOI18N
        _buttonDEL.setForeground(java.awt.Color.darkGray);
        _buttonDEL.setText("DEL");
        _buttonDEL.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                delete(evt);
            }
        });

        _buttonAC.setBackground(java.awt.Color.orange);
        _buttonAC.setFont(new java.awt.Font("Droid Sans Mono", 0, 15)); // NOI18N
        _buttonAC.setForeground(java.awt.Color.darkGray);
        _buttonAC.setText("AC");
        _buttonAC.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                reset(evt);
            }
        });

        _button7.setBackground(java.awt.Color.darkGray);
        _button7.setFont(new java.awt.Font("Droid Sans Mono", 0, 15)); // NOI18N
        _button7.setForeground(java.awt.Color.lightGray);
        _button7.setText("7");
        _button7.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                write(evt);
            }
        });

        _button8.setBackground(java.awt.Color.darkGray);
        _button8.setFont(new java.awt.Font("Droid Sans Mono", 0, 15)); // NOI18N
        _button8.setForeground(java.awt.Color.lightGray);
        _button8.setText("8");
        _button8.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                write(evt);
            }
        });

        _button9.setBackground(java.awt.Color.darkGray);
        _button9.setFont(new java.awt.Font("Droid Sans Mono", 0, 15)); // NOI18N
        _button9.setForeground(java.awt.Color.lightGray);
        _button9.setText("9");
        _button9.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                write(evt);
            }
        });

        _buttonANS.setBackground(java.awt.Color.gray);
        _buttonANS.setFont(new java.awt.Font("Droid Sans Mono", 0, 15)); // NOI18N
        _buttonANS.setForeground(java.awt.Color.darkGray);
        _buttonANS.setText("ANS");
        _buttonANS.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                write(evt);
            }
        });

        _buttonMod.setBackground(java.awt.Color.gray);
        _buttonMod.setFont(new java.awt.Font("Droid Sans Mono", 0, 15)); // NOI18N
        _buttonMod.setForeground(java.awt.Color.darkGray);
        _buttonMod.setText("%");
        _buttonMod.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                write(evt);
            }
        });

        _button4.setBackground(java.awt.Color.darkGray);
        _button4.setFont(new java.awt.Font("Droid Sans Mono", 0, 15)); // NOI18N
        _button4.setForeground(java.awt.Color.lightGray);
        _button4.setText("4");
        _button4.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                write(evt);
            }
        });

        _button5.setBackground(java.awt.Color.darkGray);
        _button5.setFont(new java.awt.Font("Droid Sans Mono", 0, 15)); // NOI18N
        _button5.setForeground(java.awt.Color.lightGray);
        _button5.setText("5");
        _button5.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                write(evt);
            }
        });

        _button6.setBackground(java.awt.Color.darkGray);
        _button6.setFont(new java.awt.Font("Droid Sans Mono", 0, 15)); // NOI18N
        _button6.setForeground(java.awt.Color.lightGray);
        _button6.setText("6");
        _button6.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                write(evt);
            }
        });

        _buttonPro.setBackground(java.awt.Color.gray);
        _buttonPro.setFont(new java.awt.Font("Droid Sans Mono", 0, 15)); // NOI18N
        _buttonPro.setForeground(java.awt.Color.darkGray);
        _buttonPro.setText("x");
        _buttonPro.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                write(evt);
            }
        });

        _buttonDiv.setBackground(java.awt.Color.gray);
        _buttonDiv.setFont(new java.awt.Font("Droid Sans Mono", 0, 15)); // NOI18N
        _buttonDiv.setForeground(java.awt.Color.darkGray);
        _buttonDiv.setText("÷");
        _buttonDiv.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                write(evt);
            }
        });

        _button1.setBackground(java.awt.Color.darkGray);
        _button1.setFont(new java.awt.Font("Droid Sans Mono", 0, 15)); // NOI18N
        _button1.setForeground(java.awt.Color.lightGray);
        _button1.setText("1");
        _button1.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                write(evt);
            }
        });

        _button2.setBackground(java.awt.Color.darkGray);
        _button2.setFont(new java.awt.Font("Droid Sans Mono", 0, 15)); // NOI18N
        _button2.setForeground(java.awt.Color.lightGray);
        _button2.setText("2");
        _button2.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                write(evt);
            }
        });

        _button3.setBackground(java.awt.Color.darkGray);
        _button3.setFont(new java.awt.Font("Droid Sans Mono", 0, 15)); // NOI18N
        _button3.setForeground(java.awt.Color.lightGray);
        _button3.setText("3");
        _button3.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                write(evt);
            }
        });

        _buttonSum.setBackground(java.awt.Color.gray);
        _buttonSum.setFont(new java.awt.Font("Droid Sans Mono", 0, 15)); // NOI18N
        _buttonSum.setForeground(java.awt.Color.darkGray);
        _buttonSum.setText("+");
        _buttonSum.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                write(evt);
            }
        });

        _buttonSub.setBackground(java.awt.Color.gray);
        _buttonSub.setFont(new java.awt.Font("Droid Sans Mono", 0, 15)); // NOI18N
        _buttonSub.setForeground(java.awt.Color.darkGray);
        _buttonSub.setText("-");
        _buttonSub.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                write(evt);
            }
        });

        _button0.setBackground(java.awt.Color.darkGray);
        _button0.setFont(new java.awt.Font("Droid Sans Mono", 0, 15)); // NOI18N
        _button0.setForeground(java.awt.Color.lightGray);
        _button0.setText("0");
        _button0.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                write(evt);
            }
        });

        _buttonDot.setBackground(java.awt.Color.darkGray);
        _buttonDot.setFont(new java.awt.Font("Droid Sans Mono", 0, 15)); // NOI18N
        _buttonDot.setForeground(java.awt.Color.lightGray);
        _buttonDot.setLabel("·");
        _buttonDot.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                write(evt);
            }
        });

        _buttonExp.setBackground(java.awt.Color.darkGray);
        _buttonExp.setFont(new java.awt.Font("Droid Sans Mono", 0, 15)); // NOI18N
        _buttonExp.setForeground(java.awt.Color.lightGray);
        _buttonExp.setText("<html>x10<sup>■</sup></html>");
        _buttonExp.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                write(evt);
            }
        });

        _buttonResult.setBackground(java.awt.Color.gray);
        _buttonResult.setFont(new java.awt.Font("Droid Sans Mono", 0, 15)); // NOI18N
        _buttonResult.setForeground(java.awt.Color.darkGray);
        _buttonResult.setText("=");
        _buttonResult.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                calculate(evt);
            }
        });

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(getContentPane());
        getContentPane().setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addContainerGap()
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addComponent(_textResult, javax.swing.GroupLayout.Alignment.TRAILING)
                    .addGroup(layout.createSequentialGroup()
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.TRAILING)
                            .addGroup(layout.createSequentialGroup()
                                .addComponent(_buttonOP, javax.swing.GroupLayout.PREFERRED_SIZE, 70, javax.swing.GroupLayout.PREFERRED_SIZE)
                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                                .addComponent(_buttonCP, javax.swing.GroupLayout.PREFERRED_SIZE, 70, javax.swing.GroupLayout.PREFERRED_SIZE)
                                .addGap(82, 82, 82)
                                .addComponent(_buttonDEL, javax.swing.GroupLayout.PREFERRED_SIZE, 70, javax.swing.GroupLayout.PREFERRED_SIZE))
                            .addGroup(javax.swing.GroupLayout.Alignment.LEADING, layout.createSequentialGroup()
                                .addComponent(_button4, javax.swing.GroupLayout.PREFERRED_SIZE, 70, javax.swing.GroupLayout.PREFERRED_SIZE)
                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                .addComponent(_button5, javax.swing.GroupLayout.PREFERRED_SIZE, 70, javax.swing.GroupLayout.PREFERRED_SIZE)
                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                .addComponent(_button6, javax.swing.GroupLayout.PREFERRED_SIZE, 70, javax.swing.GroupLayout.PREFERRED_SIZE)
                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                .addComponent(_buttonPro, javax.swing.GroupLayout.PREFERRED_SIZE, 70, javax.swing.GroupLayout.PREFERRED_SIZE)))
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                            .addComponent(_buttonDiv, javax.swing.GroupLayout.PREFERRED_SIZE, 70, javax.swing.GroupLayout.PREFERRED_SIZE)
                            .addComponent(_buttonAC, javax.swing.GroupLayout.PREFERRED_SIZE, 70, javax.swing.GroupLayout.PREFERRED_SIZE)))
                    .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, layout.createSequentialGroup()
                        .addGap(0, 0, Short.MAX_VALUE)
                        .addComponent(_button0, javax.swing.GroupLayout.PREFERRED_SIZE, 70, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent(_buttonDot, javax.swing.GroupLayout.PREFERRED_SIZE, 70, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent(_buttonExp, javax.swing.GroupLayout.PREFERRED_SIZE, 70, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent(_buttonResult, javax.swing.GroupLayout.PREFERRED_SIZE, 146, javax.swing.GroupLayout.PREFERRED_SIZE))
                    .addGroup(layout.createSequentialGroup()
                        .addComponent(_button1, javax.swing.GroupLayout.PREFERRED_SIZE, 70, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent(_button2, javax.swing.GroupLayout.PREFERRED_SIZE, 70, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent(_button3, javax.swing.GroupLayout.PREFERRED_SIZE, 70, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent(_buttonSum, javax.swing.GroupLayout.PREFERRED_SIZE, 70, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent(_buttonSub, javax.swing.GroupLayout.PREFERRED_SIZE, 70, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addGap(0, 0, Short.MAX_VALUE))
                    .addGroup(layout.createSequentialGroup()
                        .addComponent(_button7, javax.swing.GroupLayout.PREFERRED_SIZE, 70, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent(_button8, javax.swing.GroupLayout.PREFERRED_SIZE, 70, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent(_button9, javax.swing.GroupLayout.PREFERRED_SIZE, 70, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent(_buttonANS, javax.swing.GroupLayout.PREFERRED_SIZE, 70, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                        .addComponent(_buttonMod, javax.swing.GroupLayout.PREFERRED_SIZE, 70, javax.swing.GroupLayout.PREFERRED_SIZE)))
                .addContainerGap())
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addContainerGap()
                .addComponent(_textResult, javax.swing.GroupLayout.PREFERRED_SIZE, 70, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(_buttonOP, javax.swing.GroupLayout.PREFERRED_SIZE, 70, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(_buttonCP, javax.swing.GroupLayout.PREFERRED_SIZE, 70, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(_buttonDEL, javax.swing.GroupLayout.PREFERRED_SIZE, 70, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(_buttonAC, javax.swing.GroupLayout.PREFERRED_SIZE, 70, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(_button7, javax.swing.GroupLayout.PREFERRED_SIZE, 70, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(_button8, javax.swing.GroupLayout.PREFERRED_SIZE, 70, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(_button9, javax.swing.GroupLayout.PREFERRED_SIZE, 70, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(_buttonMod, javax.swing.GroupLayout.PREFERRED_SIZE, 70, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(_buttonANS, javax.swing.GroupLayout.PREFERRED_SIZE, 70, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(_button4, javax.swing.GroupLayout.PREFERRED_SIZE, 70, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(_button5, javax.swing.GroupLayout.PREFERRED_SIZE, 70, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(_button6, javax.swing.GroupLayout.PREFERRED_SIZE, 70, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(_buttonPro, javax.swing.GroupLayout.PREFERRED_SIZE, 70, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(_buttonDiv, javax.swing.GroupLayout.PREFERRED_SIZE, 70, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(_button1, javax.swing.GroupLayout.PREFERRED_SIZE, 70, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(_button2, javax.swing.GroupLayout.PREFERRED_SIZE, 70, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(_button3, javax.swing.GroupLayout.PREFERRED_SIZE, 70, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(_buttonSum, javax.swing.GroupLayout.PREFERRED_SIZE, 70, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(_buttonSub, javax.swing.GroupLayout.PREFERRED_SIZE, 70, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                        .addComponent(_button0, javax.swing.GroupLayout.PREFERRED_SIZE, 70, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addComponent(_buttonDot, javax.swing.GroupLayout.PREFERRED_SIZE, 70, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addComponent(_buttonResult, javax.swing.GroupLayout.PREFERRED_SIZE, 70, javax.swing.GroupLayout.PREFERRED_SIZE))
                    .addComponent(_buttonExp, javax.swing.GroupLayout.PREFERRED_SIZE, 70, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addContainerGap(javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
        );

        pack();
    }// </editor-fold>//GEN-END:initComponents

    private void write(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_write
        _textResult.setHorizontalAlignment( JTextField.LEFT );
        javax.swing.JButton button;
        button = ( javax.swing.JButton ) evt.getSource();
        String buttonText = button.getText();
        buttonText = buttonText.replace( "·", "." );
        buttonText = buttonText.replace( "<html>x10<sup>■</sup></html>", "e" );
        if( !_isResult ) {
            _textResult.setText( _textResult.getText() + buttonText );
        }
        else {
            if( "+".equals( buttonText ) || "-".equals( buttonText ) ||
                "x".equals( buttonText ) || "÷".equals( buttonText ) ||
                "e".equals( buttonText ) || "%".equals( buttonText ) ) {
                _textResult.setText( "ANS" + buttonText );
            }
            else {
                _textResult.setText( buttonText );
            }
            _isResult = false;
        }
    }//GEN-LAST:event_write

    private void calculate(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_calculate
        if( !_isResult ) {
            ScriptEngineManager mgr = new ScriptEngineManager();
            ScriptEngine engine = mgr.getEngineByName( "JavaScript" );
            String result = _textResult.getText();
            result = result.replace( "x", "*" );
            result = result.replace( "÷", "/" );
            result = result.replaceAll( "ANS", _ans );
            try {
                _textResult.setHorizontalAlignment( JTextField.RIGHT );
                _textResult.setText( String.valueOf( engine.eval( result ) ) );
                _ans = String.valueOf( engine.eval( result ) );
            }
            catch( ScriptException ex ) {
                _textResult.setText( "Syntax ERROR" );
            }
            _isResult = true;
        }
    }//GEN-LAST:event_calculate

    private void reset(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_reset
        _textResult.setText( "" );
    }//GEN-LAST:event_reset

    private void delete(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_delete
        if( !"".equals( _textResult.getText() ) && !_isResult ) {
            _textResult.setText(
                _textResult.getText().substring( 0, _textResult.getText().length()-1 )
            );
        }
    }//GEN-LAST:event_delete

    /**
     * @param args the command line arguments
     */
    public static void main(String args[]) {
        /* Set the Nimbus look and feel */
        //<editor-fold defaultstate="collapsed" desc=" Look and feel setting code (optional) ">
        /* If Nimbus (introduced in Java SE 6) is not available, stay with the default look and feel.
         * For details see http://download.oracle.com/javase/tutorial/uiswing/lookandfeel/plaf.html 
         */
        try {
            for (javax.swing.UIManager.LookAndFeelInfo info : javax.swing.UIManager.getInstalledLookAndFeels()) {
                if ("Nimbus".equals(info.getName())) {
                    javax.swing.UIManager.setLookAndFeel(info.getClassName());
                    break;
                }
            }
        } catch (ClassNotFoundException ex) {
            java.util.logging.Logger.getLogger(Calculator.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (InstantiationException ex) {
            java.util.logging.Logger.getLogger(Calculator.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (IllegalAccessException ex) {
            java.util.logging.Logger.getLogger(Calculator.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (javax.swing.UnsupportedLookAndFeelException ex) {
            java.util.logging.Logger.getLogger(Calculator.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        }
        //</editor-fold>

        /* Create and display the form */
        java.awt.EventQueue.invokeLater(new Runnable() {
            public void run() {
                new Calculator().setVisible(true);
            }
        });
    }

    private String _ans = "_";
    private boolean _isResult = false;
    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JButton _button0;
    private javax.swing.JButton _button1;
    private javax.swing.JButton _button2;
    private javax.swing.JButton _button3;
    private javax.swing.JButton _button4;
    private javax.swing.JButton _button5;
    private javax.swing.JButton _button6;
    private javax.swing.JButton _button7;
    private javax.swing.JButton _button8;
    private javax.swing.JButton _button9;
    private javax.swing.JButton _buttonAC;
    private javax.swing.JButton _buttonANS;
    private javax.swing.JButton _buttonCP;
    private javax.swing.JButton _buttonDEL;
    private javax.swing.JButton _buttonDiv;
    private javax.swing.JButton _buttonDot;
    private javax.swing.JButton _buttonExp;
    private javax.swing.JButton _buttonMod;
    private javax.swing.JButton _buttonOP;
    private javax.swing.JButton _buttonPro;
    private javax.swing.JButton _buttonResult;
    private javax.swing.JButton _buttonSub;
    private javax.swing.JButton _buttonSum;
    private javax.swing.JTextField _textResult;
    // End of variables declaration//GEN-END:variables
}
