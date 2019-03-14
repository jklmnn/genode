
with Cai.Log;
with Cai.Log.Client;

procedure Component
is
   I : constant Integer := 42;
   L : constant Long_Integer := 4398046511104;
   NI : constant Integer := -42;
   NL : constant Long_Integer := -4398046511104;
   U : constant Cai.Log.Unsigned := 16#deadbeef#;
begin
   Cai.Log.Client.Stdout ("Log message");
   Cai.Log.Client.Stderr ("Error message");
   Cai.Log.Client.Stdout ("Integer: " & Cai.Log.Image (I));
   Cai.Log.Client.Stdout ("Negative Integer: " & Cai.Log.Image (NI));
   Cai.Log.Client.Stdout ("Long_Integer: " & Cai.Log.Image (L));
   Cai.Log.Client.Stdout ("Negative Long_Integer: " & Cai.Log.Image (NL));
   Cai.Log.Client.Stdout ("Smallest Integer: " & Cai.Log.Image (Integer'First));
   Cai.Log.Client.Stdout ("Smallest Long_Integer: " & Cai.Log.Image (Long_Integer'First));
   Cai.Log.Client.Stdout ("Largest Integer: " & Cai.Log.Image (Integer'Last));
   Cai.Log.Client.Stdout ("Largest Long_Integer: " & Cai.Log.Image (Long_Integer'Last));
   Cai.Log.Client.Stdout ("True: " & Cai.Log.Image (True));
   Cai.Log.Client.Stdout ("False: " & Cai.Log.Image (False));
   Cai.Log.Client.Stdout ("Hex value: " & Cai.Log.Image (U));
   Cai.Log.Client.Stdout ("Smallest hex value: " & Cai.Log.Image (Cai.Log.Unsigned'First));
   Cai.Log.Client.Stdout ("Largest hex value: " & Cai.Log.Image (Cai.Log.Unsigned'Last));
end Component;
