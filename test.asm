<pg>
  <odv>
    <ldv>
      <dv>
        <mot_clef>entier</mot_clef>
        <id_variable>$a</id_variable>
        <ott>
        </ott>
      </dv>
      <ldvb>
        <symbole>VIRGULE</symbole>
        <dv>
          <mot_clef>entier</mot_clef>
          <id_variable>$b</id_variable>
          <ott>
          </ott>
        </dv>
        <ldvb>
        </ldvb>
      </ldvb>
    </ldv>
    <symbole>POINT_VIRGULE</symbole>
  </odv>
  <ldf>
    <df>
      <id_fonction>main</id_fonction>
      <lp>
        <symbole>PARENTHESE_OUVRANTE</symbole>
        <oldv>
        </oldv>
        <symbole>PARENTHESE_FERMANTE</symbole>
      </lp>
      <odv>
      </odv>
      <ib>
        <symbole>ACCOLADE_OUVRANTE</symbole>
        <li>
          <i>
            <iaff>
              <var>
                <id_variable>$a</id_variable>
                <oind>
                </oind>
              </var>
              <symbole>EGAL</symbole>
              <exp>
                <conj>
                  <comp>
                    <e>
                      <t>
                        <neg>
                          <f>
                            <mot_clef>lire</mot_clef>
                            <symbole>PARENTHESE_OUVRANTE</symbole>
                            <symbole>PARENTHESE_FERMANTE</symbole>
                          </f>
                        </neg>
                        <tb>
                        </tb>
                      </t>
                      <eb>
                      </eb>
                    </e>
                    <compb>
                    </compb>
                  </comp>
                  <conjb>
                  </conjb>
                </conj>
                <expb>
                </expb>
              </exp>
              <symbole>POINT_VIRGULE</symbole>
            </iaff>
          </i>
          <li>
            <i>
              <iaff>
                <var>
                  <id_variable>$b</id_variable>
                  <oind>
                  </oind>
                </var>
                <symbole>EGAL</symbole>
                <exp>
                  <conj>
                    <comp>
                      <e>
                        <t>
                          <neg>
                            <f>
                              <var>
                                <id_variable>$a</id_variable>
                                <oind>
                                </oind>
                              </var>
                            </f>
                          </neg>
                          <tb>
                            <symbole>FOIS</symbole>
                            <neg>
                              <f>
                                <var>
                                  <id_variable>$a</id_variable>
                                  <oind>
                                  </oind>
                                </var>
                              </f>
                            </neg>
                            <tb>
                            </tb>
                          </tb>
                        </t>
                        <eb>
                        </eb>
                      </e>
                      <compb>
                      </compb>
                    </comp>
                    <conjb>
                    </conjb>
                  </conj>
                  <expb>
                  </expb>
                </exp>
                <symbole>POINT_VIRGULE</symbole>
              </iaff>
            </i>
            <li>
              <i>
                <iecr>
                  <mot_clef>ecrire</mot_clef>
                  <symbole>PARENTHESE_OUVRANTE</symbole>
                  <exp>
                    <conj>
                      <comp>
                        <e>
                          <t>
                            <neg>
                              <f>
                                <var>
                                  <id_variable>$b</id_variable>
                                  <oind>
                                  </oind>
                                </var>
                              </f>
                            </neg>
                            <tb>
                            </tb>
                          </t>
                          <eb>
                          </eb>
                        </e>
                        <compb>
                        </compb>
                      </comp>
                      <conjb>
                      </conjb>
                    </conj>
                    <expb>
                    </expb>
                  </exp>
                  <symbole>PARENTHESE_FERMANTE</symbole>
                  <symbole>POINT_VIRGULE</symbole>
                </iecr>
              </i>
              <li>
              </li>
            </li>
          </li>
        </li>
        <symbole>ACCOLADE_FERMANTE</symbole>
      </ib>
    </df>
    <ldf>
    </ldf>
  </ldf>
</pg>
$a resw 1
$b resw 1
call readline
mov eax, sinput
call atoi
push eax
pop ebx
mov [$a], ebx
push [$a]
push [$a]
pop ebx
pop eax
mul eax, ebx
push eax
pop ebx
mov [$b], ebx
push [$b]
pop eax
call iprintLF
