/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author EMRE KAVAK
 */
import javax.swing.JPanel;
import java.awt.*;
import java.awt.event.*;
import javax.swing.JOptionPane;
import java.util.*;
import javafx.scene.shape.Circle;
import java.awt.Graphics;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import javax.swing.JFrame;
import javax.swing.Icon;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JComponent;
import javax.swing.JLabel;
import java.awt.event.MouseListener;
import java.util.Random;

public class TEST {
    public static void main(String[] args) {
        ConnectFour obje = new ConnectFour();    
        obje.input();
    }  
}
