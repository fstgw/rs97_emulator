/*
 * @(#)AWTException.java	1.17 06/10/10
 *
 * Copyright  1990-2008 Sun Microsystems, Inc. All Rights Reserved.
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License version
 * 2 only, as published by the Free Software Foundation. 
 * 
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License version 2 for more details (a copy is
 * included at /legal/license.txt). 
 * 
 * You should have received a copy of the GNU General Public License
 * version 2 along with this work; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 * 02110-1301 USA 
 * 
 * Please contact Sun Microsystems, Inc., 4150 Network Circle, Santa
 * Clara, CA 95054 or visit www.sun.com if you need additional
 * information or have any questions. 
 *
 */
package java.awt;

/**
 * Signals that an Absract Window Toolkit exception has occurred.
 *
 * @version 	1.13 08/19/02
 * @author 	Arthur van Hoff
 */
public class AWTException extends Exception {
    /*
     * JDK 1.1 serialVersionUID 
     */
    private static final long serialVersionUID = -1900414231151323879L;
    /**
     * Constructs an instance of <code>AWTException</code> with the 
     * specified detail message. A detail message is an 
     * instance of <code>String</code> that describes this particular
     * exception. 
     * @param   msg     the detail message
     * @since   JDK1.0
     */
    public AWTException(String msg) {
        super(msg);
    }
}
