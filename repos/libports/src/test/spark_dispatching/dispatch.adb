
with Parent;
with Child;

package body Dispatch
is
   type Result_Table_Type is array (Boolean'Range) of Integer;
   Result_Table : constant Result_Table_Type := (True  => 0,
                                                 False => -1);

   procedure Run (Result : out Integer)
   is
      P : Parent.Object;
      C : Child.Object;
      function Is_Parent (O : Parent.Object'Class) return Boolean
      is
      begin
         return O.Is_Parent;
      end Is_Parent;
   begin
      Result := Result_Table (P.Is_Parent
                              and then not C.Is_Parent
                              and then Is_Parent (P)
                              and then not Is_Parent (C));
   end Run;

end Dispatch;
